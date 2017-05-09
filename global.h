#ifndef GLOBAL_H
#define GLOBAL_H


#include <QVector>
#include <QBitArray>
#include <QSemaphore>


#define ChanNumber 4
#define filteredDataNumber 1500
#define BufferSize (8192000 * 4)

//extern const int ChanNumber;
//extern const int filteredDataNumber;
//extern const int BufferSize;

extern qint16 m_pdmData[ChanNumber][BufferSize];
extern QSemaphore freeSpace;
extern QSemaphore usedSpace;
extern volatile bool flag;
extern volatile bool flagComp;

extern volatile qint64 workerAllDataCount;
extern volatile qint64 widgetAllDataCount;


#endif // GLOBAL_H
