#include <unistd.h> // for sleep ?

#include "flow.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>


QReadWriteLock flowlockA;
QReadWriteLock flowlockC;
QReadWriteLock flowlockG;
QReadWriteLock flowlockT;

flow::flow(QObject *parent) :
    QObject(parent)
{

}

int flow::getflow(const char flowname) 
{

	qDebug() << "getting flow from thr : " ;
  // do some work !
	int r = rand() % 20;
		  switch(flowname) {
			case 'A' : 
					if (r == 0) {
						qDebug() << "A write from thr : " ;
						QWriteLocker locker( &flowlockA );
						sleep( 3 ); // generate file
				  } else {
						qDebug() << "A read from thr : " ;
						QReadLocker locker( &flowlockA );
				  }
				break;
			case 'C' : 
					if (r == 0) {
						qDebug() << "C write from thr : " ;
						QWriteLocker locker( &flowlockC );
						sleep( 3 ); // generate file
				  } else {
						qDebug() << "C read from thr : " ;
						QReadLocker locker( &flowlockC );
				  }
				break;
			case 'G' :
					if (r == 0) {
						qDebug() << "G write from thr : "  ;
						QWriteLocker locker( &flowlockG );
						sleep( 3 ); // generate file
				  } else {
						qDebug() << "G read from thr : " ;
						QReadLocker locker( &flowlockG );
				  }
				break;
			case 'T' :
					if (r == 0) {
						qDebug() << "T write from thr : ";
						QWriteLocker locker( &flowlockT );
						sleep( 3 ); // generate file
				  } else {
						qDebug() << "T read from thr : " ;
						QReadLocker locker( &flowlockT );
				  }
				break;
		  }

  return r;
}
