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
 */

#include "producer.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>

#include "work.h"

extern int DataSize;

Producer::Producer(WorkQ* q,QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
    queue = q;
}

void Producer::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request producer start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Producer::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request producer aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Producer::doWork()
{
    qDebug()<<"Starting producer process in Thread "<<thread()->currentThreadId();

     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
     for (int i = 0; i < DataSize; ++i) {
        // Checks if the process should be aborted
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();

        if (abort) {
            qDebug()<<"Aborting producer process in Thread "<<thread()->currentThreadId();
            break;
        }

        queue->add("ACGT"[(int)qrand() % 4]);
	//emit bufferFillCountChanged(usedBytes.available());
        //emit producerCountChanged(i);
     }

    // signal poison pills
    // for ech consumer ?
    queue->add('P');
    queue->add('P');

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Producer process finished in Thread "<<thread()->currentThreadId();

    emit finished();
}
