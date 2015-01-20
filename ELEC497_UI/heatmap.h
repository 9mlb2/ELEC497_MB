#ifndef HEATMAP_H
#define HEATMAP_H

#include <QImage>
#include <vector>
#include <QColor>
#include "datapoint.h"
#include <iostream>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QRect>


using namespace std;

class HeatMap: public QImage
{

public:
    HeatMap(QSize size, QImage::Format form);

    void genMap(vector<DataPoint> vec);
    void update();
    static const float RADC = 0.5; //fudge factor for pressure algorithm
    void applyMask(const QImage &mask);

private:



};

#endif // HEATMAP_H
