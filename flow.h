/*
   Copyright 2016 

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

#ifndef FLOW_H
#define FLOW_H

#include <QObject>
#include <QMutex>
#include <QReadWriteLock>


class flow : public QObject
{
    Q_OBJECT

public:
    explicit flow(QObject *parent = 0);

	  int getflow(const char flowname);

private:

};

#endif // FLOW_H
