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


#include "consumer.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>

#include "work.h"
#include "flow.h"

extern int DataSize;

Consumer::Consumer(WorkQ* q,QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;

    queue = q;

}

void Consumer::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request consumer start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Consumer::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request consumer aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Consumer::doWork()
{
    qDebug()<<"Starting consumer process in Thread "<<thread()->currentThreadId();

    for (int i = 0; i < DataSize; ++i) {
    volatile char item;

      // Checks if the process should be aborted
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();

        if (abort) {
            qDebug()<<"Aborting consumer process in Thread "<<thread()->currentThreadId();
            break;
        }

	//qDebug() << "from thr : " << thread()->currentThreadId();
	item = queue->remove();
	if (item == 'P') {
	  // got poison pills !
	  fprintf(stderr,"got poison pills\n");
	  break;
	}
			  // do some work !
			  flow myfile;
		    myfile.getflow(item);
        fprintf(stderr, "%c", item);
     }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Consumer process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finished();
}
