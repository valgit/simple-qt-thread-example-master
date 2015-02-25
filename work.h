
#ifndef WORK_H
#define WORK_H

#include <QtCore>
#include <QThread>

#include <stdio.h>
#include <stdlib.h>

class WorkQ {

private:
	int BufferSize;
	char *buffer;

	QSemaphore *freeBytes;
	QSemaphore *usedBytes;

	volatile int m_Read;
	volatile int m_Write;
public:
	WorkQ(int Size);
	~WorkQ();
	
	char remove();
	void add(char c);
};

#endif /* WORK_H */

