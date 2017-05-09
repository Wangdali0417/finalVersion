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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QVector>
#include <QtCore/QTimer>
#include <QBitArray>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QValueAxis>
#include <iostream>
#include <QGridLayout>
#include <QGroupBox>
#include <QtGlobal>
#include <QThread>
#include <QString>
#include <QDebug>
#include <ctime>
#include "lowpassfilterparam.h"
#include "worker.h"
#include "global.h"


QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//class XYSeriesIODevice;

//class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void filter();

public:
    QTimer m_timer;

public slots:
    //void plot();
    void handleTimeout();
    //void cont();
    void changeFlag();
    void changeFlagComp();

private:

    QChart *m_chart;
    QVector<QLineSeries *> m_series;
    qint64 count;
    qint64 m_channelNumber;

    qint64 bufferPosition[ChanNumber];
    qint64 m_filteredData[ChanNumber][filteredDataNumber];
    qint64 filteredPosition[ChanNumber];
    qint64 filteredDataCount[ChanNumber];
    enum {plotInterval = 100, sampleRange = 14000, timeInterval = 1000, sampleInterval = 10, filteredRange = 1024 * 8 * 100};
};

#endif // WIDGET_H
