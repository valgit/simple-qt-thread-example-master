#include <unistd.h> // for sleep ?

#include "flow.h"
#include <QTimer>
#include <QEventLoop>

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>


QMutex flowlock;
QHash<QChar, QMutex*> flowfiles;


flow::flow(QObject *parent) :
    QObject(parent)
{

}

int flow::getflow(const char flowname) 
{
  QMutex* flow; // mutex on our file

	//qDebug() << "getting flow from thr : " ;
  // do some work !
	int r = rand() % 10;

  QMutexLocker locker(&flowlock);
  if (flowfiles.contains(flowname)) {
		flow = flowfiles.value(flowname);
  } else {
	  qDebug() << "create mutex flow" ;
	  flow = new QMutex();
	  flowfiles.insert(flowname,flow); 
	  
  }
  locker.unlock();

  // we have a mutex on flow file !
  QMutexLocker lockflow(flow);

	if (r == 0) {
						//qDebug() << "write from thr : " << flowname ;
						sleep( 1 ); // generate file
	} /*
else {
						qDebug() << "read from thr : " << flowname ;
	} */

  return r;
}
