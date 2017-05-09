 /****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "widget.h"
using namespace std;


QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_chart(0),
      m_series(4),
      count(0),
      m_channelNumber(4)//if channelnumber is added, should be changed!!!
{

    for(qint64 i = 0; i < ChanNumber; i++)
    {
        bufferPosition[ChanNumber] = 0;
    }
    QVBoxLayout *m_layout = new QVBoxLayout;


    for(qint64 i = 0; i < m_channelNumber; i++){

        m_chart = new QChart;
        QChartView *chartView = new QChartView(m_chart);
        chartView->setMinimumSize(1000,600);
        m_series[i] = new QLineSeries;
        m_chart->addSeries(m_series[i]);
        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(0, sampleRange);
        axisX->setLabelFormat("%g");
        axisX->setTitleText("Samples");
        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(11500,15000);
        axisY->setTitleText("Audio level");
        m_chart->setAxisX(axisX, m_series[i]);
        m_chart->setAxisY(axisY, m_series[i]);
        m_chart->legend()->hide();
        m_chart->setTitle("Data from the microphone");

        m_layout->addWidget(chartView);
    }

    setLayout(m_layout);


    //Worker initial

    //Worker *wk = new Worker();
//    wk->moveToThread(&workerThread);
//    QObject::connect(&workerThread, SIGNAL(finished()), wk, SLOT(deleteLater()));
    // QObject::connect(wk, SIGNAL(showText(QString)), this, SLOT(showText(QString)));
    // QObject::connect(m_button, SIGNAL(clicked()), wk, SLOT(doWork()));
    // QObject::connect(wk, SIGNAL(cont()), this, SLOT(cont()));
    //QObject::connect(m_button1, SIGNAL(clicked()), this, SLOT(changeFlag()));
    //QObject::connect(wk, SIGNAL(changeFlagComp()), this, SLOT(changeFlagComp()));

    //workerThread.start();
    //Timer initialS
    //QObject::connect(wk, SIGNAL(plot()), &m_timer, SLOT(start()));
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    //m_timer.setInterval(timeInterval);
    m_timer.interval();
    //m_timer.setInterval(2000);
    //m_timer.start();

}

Widget::~Widget()
{
//    workerThread.quit();
//    workerThread.wait();
}


void Widget::handleTimeout()
{

//    qDebug() << "if plot() start internally";

    double time_start = (double)clock();



    this->filter();




    qint64 maxSize;
    qint64 range;
    qint64 size;
//    for(qint64 i = 0; i < filteredDataCount[0]; i++)
//    {
//       qDebug() << m_filteredData[0][i] << " ";
//    }


    for(qint64 n = 0; n < m_channelNumber; n++)
    {

        QVector<QPointF> oldPoints;
        QVector<QPointF> points;


        maxSize = filteredDataCount[n];
        range = sampleRange;
        //qDebug() <<maxSize;

        oldPoints = m_series[n]->pointsVector();


        if (oldPoints.count() < range) {
            points = m_series[n]->pointsVector();
        } else {
            for (qint64 i = maxSize; i < oldPoints.count(); i++)
                points.append(QPointF(i - maxSize, oldPoints.at(i).y()));
        }

        size = points.count();
        for (qint64 k = 0; k < maxSize; k++)
            points.append(QPointF((k + size), (qint16)m_filteredData[n][k]));

        m_series[n]->replace(points);
    }
   double time_end = (double)clock();
   qDebug() << "plot + filter: " << QString::number(time_end - time_start) << "\n";

}




//void Widget::showText(const QString &str)
//{
//    m_text_browser->append(str);
//}

//void Widget::cont()
//{
//    m_button1->setHidden(false);

//}

// filter
void Widget::filter()
{
//    qDebug() << "filter internal widgetAllData :" << widgetAllDataCount << "\n";
//    qDebug() << "flagComp: " << flagComp << "\n";
    if(flagComp)
    {
        if(widgetAllDataCount > workerAllDataCount)
        {
            qDebug() <<"if stop, widgetAllDataCount: " << widgetAllDataCount << "\n";
            m_timer.stop();
        }
    }
    //double time_start = (double)clock();
    lowpassfilter lpfilter;

    widgetAllDataCount += filteredRange;
    for(qint64 i = 0; i< ChanNumber; i++)
    {
        filteredPosition[i] = 0;
    }

    usedSpace.acquire(filteredRange);
//    qDebug() << "widget usedSpace: " << usedSpace.available();
    for(qint64 j = 0; j < m_channelNumber; j++)
    {

        //qDebug() << "bufferPosition[" << j << "]: " << bufferPosition[j];


        for(qint64 n = 0; n < filteredRange; n += 4096){

            //usedSpace.acquire(4096);
            qint64 sum = 0;
//            qDebug() << "widget freeSpace: " << freeSpace.available();
//            qDebug() << "widget usedSpace: " << usedSpace.available();
            qint64 temPosition = bufferPosition[j];

            for(qint64 i = 0; i < lpfilter.coeffiLength; i++){

//                usedSpace.acquire(1024/(lpfilter.coeffiLength-1));


                //usedSpace.acquire();

                //qDebug() << "widget usedSpace: " << usedSpace.available();
                sum = sum + m_pdmData[j][temPosition] * lpfilter.filterCoefficients[lpfilter.coeffiLength-1-i];
//                freeSpace.release(1024/(lpfilter.coeffiLength-1));


                //freeSpace.release();

                //qDebug() << "widget freeSpace: " << freeSpace.available();
                temPosition++;
            }

            bufferPosition[j] = (bufferPosition[j] + 4096) % BufferSize;
            m_filteredData[j][filteredPosition[j]++] = sum;//notice
           //freeSpace.release(4096);

        }
        filteredDataCount[j] = filteredPosition[j];
    }
    freeSpace.release(filteredRange);
//    qDebug() << "widget freeSpace: " << freeSpace.available();


    //double time_end = (double)clock();
    //qDebug() << "filter: " << QString::number(time_end - time_start) << "\n";
}

void Widget::changeFlag()
{
    flag = false;
    //qDebug() << "flag " + QString::number(flag);
}

void Widget::changeFlagComp()
{
    flagComp = true;
    //qDebug() << "flag " + QString::number(flag);
}

