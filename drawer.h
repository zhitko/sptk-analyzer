#ifndef DRAWER_H
#define DRAWER_H

#include <QMap>

#include "defines.h"

#include <mgl2/qmathgl.h>

#define GRAPH_Y_VAL_MAX 10000

#include "dp/vectordp.h"
#include "dp/spectrdp.h"
#include "dataprocessing.h"

extern "C" {
    #include "analysis/metrics.h"
    #include "openal/wavFile.h"
    #include "./sptk/SPTK.h"
    #include "./sptk/vector.h"
}

mglData * createMglData(vector vec, mglData * data, bool nan = false);
void vectorToData(vector vec, mglData * data);
void vectorToDataWithNan(vector vec, mglData * data);
vector scaleVectorByDPResults(vector, SpectrDP*);
vector getSignalWithMask(vector, SpectrDP*, vector);

class Drawer: public mglDraw
{
public:
    Drawer();
    virtual ~Drawer();

    bool stereo;
    bool showUMP;

    virtual int getDataLenght();
    virtual int getDataSeconds();

    virtual int Draw(mglGraph *gr);
    virtual void Proc(QString fname);
    virtual void reProc();
    double calcResultMark(vector, vector);

    void Reload();
    void Click();

    double proximity_curve_correlation, proximity_curve_integral, proximity_curve_local, proximity_average;
    double proximity_range, proximity_curve_shape;

    MetricsData getMetricData();

protected:
    GraphData * data;
    QString fileName;
    mglData *waveData, *pitchData, *pitchDataOriginal, *pitchDataDerivative, *specData, *maskData,
        *scaledMaskData, *intensiveData, *intensiveDataOriginal, *planeData;
    mglData *pWaveData, *nWaveData, *tWaveData;
    double pitchDataDerivativeZero;
    int waveDataLen;
    MetricsData metrics;
};

#endif // DRAWER_H
