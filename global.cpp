#include "global.h"


//const int ChanNumber = 4;
//const int filteredDataNumber = 150;
//const int BufferSize = 8192000;

qint16 m_pdmData[ChanNumber][BufferSize];

QSemaphore freeSpace(BufferSize);
QSemaphore usedSpace(0);

volatile bool flag = true;
volatile bool flagComp = false;

volatile qint64 workerAllDataCount = 0;
volatile qint64 widgetAllDataCount = 0;


