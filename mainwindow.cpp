/*
   Copyright 2013 Fabien Pierre-Nicolas.
      - Primarily authored by Fabien Pierre-Nicolas

   This file is part of simple-qt-thread-example, a simple example to demonstrate how to use threads.
   This example is explained on http://fabienpn.wordpress.com/qt-thread-simple-and-stable-with-sources/

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This progra is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
A
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QThread>
#include <QDebug>

int DataSize = 100000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // The thread and the worker are created in the constructor so it is always safe to delete them.
    WorkQ* queue = new WorkQ(1024);
	  int consumers = 4;
	
    pthread = new QThread();
    producer = new Producer(queue,consumers);

    producer->moveToThread(pthread);
    connect(producer, SIGNAL(valueChanged(QString)), ui->label, SLOT(setText(QString)));
    connect(producer, SIGNAL(workRequested()), pthread, SLOT(start()));
    connect(pthread, SIGNAL(started()), producer, SLOT(doWork()));
    connect(producer, SIGNAL(finished()), pthread, SLOT(quit()), Qt::DirectConnection);

    // put N consummer ?
	  for(int i=0;i<consumers;i++) {
						cthread[i] = new QThread();
						consumer[i] = new Consumer(queue);

						consumer[i]->moveToThread(cthread[i]);
						connect(consumer[i], SIGNAL(valueChanged(QString)), 
										ui->label, SLOT(setText(QString)));
						connect(consumer[i], SIGNAL(workRequested()), cthread[i], SLOT(start()));
						connect(cthread[i], SIGNAL(started()), consumer[i], 
										SLOT(doWork()));
						connect(consumer[i], SIGNAL(finished()), cthread[i], 
										SLOT(quit()), Qt::DirectConnection);
	  }


}

MainWindow::~MainWindow()
{
    producer->abort();
    pthread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete pthread;
    delete producer;

    delete cthread[0];
    delete consumer[0];

    delete cthread[1];
    delete consumer[1];

    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    // To avoid having two threads running simultaneously, the previous thread is aborted.
    producer->abort();
    pthread->wait(); // If the thread is not running, this will immediately return.

    producer->requestWork();
    consumer[0]->requestWork();
    consumer[1]->requestWork();
}
