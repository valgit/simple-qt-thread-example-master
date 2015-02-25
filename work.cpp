#include "work.h"

WorkQ::WorkQ(int size)
{
	BufferSize = size;
	buffer = new char[BufferSize];
	
	freeBytes = new QSemaphore(BufferSize);
	usedBytes = new QSemaphore;
	m_Write = 0;
	m_Read = 0;
}

WorkQ::~WorkQ()
{
	delete freeBytes;
	delete usedBytes;
	delete buffer;
}

void WorkQ::add(char c) 
{
	freeBytes->acquire();
    //fprintf(stderr,"Producer:: adding %d\n",i);
	int nextElement = (m_Write + 1) % BufferSize;
	buffer[m_Write] = c;
	m_Write = nextElement;
	usedBytes->release();
}

char WorkQ::remove()
{
	char c;

	usedBytes->acquire();
	int nextElement = (m_Read + 1) % BufferSize;
	//fprintf(stderr,"next read : %d\n",m_Read);
        c = buffer[m_Read];
        m_Read = nextElement;
	freeBytes->release();
    return c;
}
