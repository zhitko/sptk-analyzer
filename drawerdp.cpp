#include "drawerdp.h"

#include <QFile>
#include <QDebug>

#include "settingsdialog.h"

#include "DP/continuousdp.h"

extern "C" {
    #include "./OpenAL/wavFile.h"

    #include "float.h"

    #include "./SPTK/SPTK.h"
    #include "./SPTK/pitch/pitch.h"
    #include "./SPTK/x2x/x2x.h"
    #include "./SPTK/frame/frame.h"
    #include "./SPTK/window/window.h"
    #include "./SPTK/lpc/lpc.h"
    #include "./SPTK/spec/spec.h"
}

DrawerDP::DrawerDP() :
    Drawer(),
    secFileName(""),
    first(true)
{
    dpData = NULL;
    secWaveData = NULL;
    errorData = NULL;
    timeData = NULL;
    pSecData = NULL;
    nSecData = NULL;
    tSecData = NULL;
    secPitchData = NULL;
    errorMax = 0;
    errorMin = 0;
}

DrawerDP::~DrawerDP()
{
    qDebug() << "DrawerDP removed";
    if (dpData) delete dpData;
    if (secWaveData) delete secWaveData;
    if (errorData) delete errorData;
    if (timeData) delete timeData;
    if (pSecData) delete pSecData;
    if (nSecData) delete nSecData;
    if (tSecData) delete tSecData;
    if (secPitchData) delete secPitchData;
}

int DrawerDP::Draw(mglGraph *gr)
{
    qDebug() << "start drawing";

    bool isCompare = !this->secFileName.isEmpty();

    gr->DefaultPlotParam();
    gr->Clf();

    qDebug() << "waveData";
    gr->MultiPlot(1, 12, 0, 1, 1, "#");
    gr->SetRange('y', 0, 1);
    gr->Plot(*waveData, "B");
    gr->Plot(*pWaveData, "y1");
    gr->Plot(*nWaveData, "q1");
    gr->Plot(*tWaveData, "c1");

    gr->MultiPlot(1, 12, 4, 1, 6, "#");
    gr->SetRange('y', 0, 1);
    gr->Axis("Y", "");
    gr->Grid("y", "W", "");
    gr->Plot(*pitchData, "-r3");
    gr->Plot(*intensiveData, "-g3");

    if(isCompare){
        qDebug() << "secWaveData";
        gr->MultiPlot(1, 12, 1, 1, 1, "#");
        gr->SetRange('y', 0, 1);
        gr->Plot(*pSecData, "y9");
        gr->Plot(*nSecData, "q9");
        gr->Plot(*tSecData, "c9");
        gr->Plot(*secWaveData, "G");
        gr->Plot(*dpData, "R9");

        gr->MultiPlot(1, 12, 3, 1, 1, "#");
        gr->Puts(mglPoint(0,0),QString("Max: %1 Min: %2").arg(this->errorMax).arg(this->errorMin).toLocal8Bit().data(), ":C", 24);

        qDebug() << "errorData";
        gr->MultiPlot(1, 12, 4, 1, 6, "#");
        gr->SetRange('y', 0, 1);
        gr->Plot(*errorData, "-B3");
        gr->Plot(*timeData, "-R3");
//        gr->Plot(*secPitchData, "-C3");

    }

    qDebug() << "finish drawing";
    return 0;
}

void setMark(vector * vec, int pos)
{
    if (vec->x > pos)
    {
        vec->v[pos] = 1.0;
        if (pos != 0)
        {
            vec->v[pos-1] = 0.0001;
        }
        if (vec->x != pos + 1)
        {
            vec->v[pos+1] = 0.0001;
        }
    } else {
        qDebug() << "WARNING setMark ? " << (vec->x > pos) ;
        qDebug() << "WARNING setMark x " << vec->x ;
        qDebug() << "WARNING setMark pos " << pos ;
    }
}

void setMark(vector * vec, int from, int to)
{
    int i=from;
    for (i=from; i<to; i++)
    {
        vec->v[i] = 1.0;
    }
    vec->v[from] = 0.0001;
    vec->v[i] = 0.0001;
}

int getMappingValue(intvector* mapping, int index)
{
    if (index > mapping->x)
    {
        return mapping->v[mapping->x - 1];
    } else {
        return mapping->v[index];
    }
}

void getMark(vector * vec, MaskData * points, int startPos, double marksScale, intvector * mapping)
{
    for (int i=0; i<points->pointsFrom.x; i++)
    {
        int from = getMappingValue(mapping, 1.0*(points->pointsFrom.v[i])/marksScale) + startPos;
        int to = getMappingValue(mapping, 1.0*(points->pointsFrom.v[i] + points->pointsLength.v[i])/marksScale) + startPos;
        setMark(vec, from, to);
        qDebug() << "setMark pSecVector " << from << " - " << to;
    }
}

void DrawerDP::Proc(QString fname)
{
    if(first)
    {
        qDebug() << "Drawer::Proc";
        Drawer::Proc(fname);
        first = false;
    }
    else
    {
        qDebug() << "DrawerDP::Proc";
        this->secFileName = fname;

        SimpleGraphData * dataSec = SimpleProcWave2Data(this->secFileName);

        secWaveData = createMglData(dataSec->d_full_wave, secWaveData);
        qDebug() << "waveData New Filled";

        qDebug() << "Start DP";
        SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();
        int speksize = sptk_settings->spec->leng / 2 + 1;
        qDebug() << "data->d_spec " << this->data->d_spec.x;
        qDebug() << "dataSec->d_spec " << dataSec->d_spec.x;
        ContinuousDP dp(
            new SpectrSignal(copyv(this->data->d_spec), speksize),
            new SpectrSignal(copyv(dataSec->d_spec), speksize),
            1,
            sptk_settings->dp->continiusLimit
        );
        dp.applySettings(
            sptk_settings->dp->continiusKH,
            sptk_settings->dp->continiusKV,
            sptk_settings->dp->continiusKD,
            sptk_settings->dp->continiusKT
        );
        dp.calculate();
        qDebug() << "Stop DP";
        vector errorVector = dp.getErrorVector();
        int endPos = minv(errorVector);
        this->errorMax = errorVector.v[maxv(errorVector)];
        this->errorMin = errorVector.v[endPos];
        errorData = createMglData(errorVector, errorData);
        errorData->Norm();

        vector timeVector = dp.getTimeVector();
        timeData = createMglData(timeVector, timeData);
        timeData->Norm();

        qDebug() << "errorVector " << errorVector.x;
        qDebug() << "timeVector " << timeVector.x;

        int startPos = endPos - timeVector.v[endPos];
        vector dpVector = zerov(errorVector.x);
        setMark(&dpVector, startPos);
        setMark(&dpVector, endPos);
        dpData = createMglData(dpVector, dpData, true);

        freev(dpVector);
        freev(errorVector);

        intvector mapping = dp.getMapping(endPos);

        double marksScale = 1.0 * data->d_wave.x / mapping.x;
        qDebug() << "data->d_wave.x " << data->d_wave.x;
        qDebug() << "mapping " << mapping.x;
        qDebug() << "marksScale " << marksScale;

        vector pSecVector = zerov(timeVector.x);
        vector nSecVector = zerov(timeVector.x);
        vector tSecVector = zerov(timeVector.x);

        freev(timeVector);

        qDebug() << "len " << endPos - startPos ;
        qDebug() << "startPos " << startPos;
        qDebug() << "endPos " << endPos;

        getMark(&pSecVector, &data->md_p, startPos, marksScale, &mapping);
        getMark(&nSecVector, &data->md_n, startPos, marksScale, &mapping);
        getMark(&tSecVector, &data->md_t, startPos, marksScale, &mapping);

        freeiv(mapping);

        pSecData = createMglData(pSecVector, pSecData, true);
        nSecData = createMglData(nSecVector, nSecData, true);
        tSecData = createMglData(tSecVector, tSecData, true);

        freev(pSecVector);
        freev(nSecVector);
        freev(tSecVector);
/*
//        double pitchScale = 1.0 * dataSec->d_pitch_originl.x / errorVector.x;
//        int pitchFrom = 1.0 * startPos / pitchScale;
//        int pitchTo = 1.0 * endPos / pitchScale;
//        vector pitchCutted = cutv(dataSec->d_pitch_originl, pitchFrom, pitchTo);
        secPitchData = createMglData(dataSec->d_pitch_originl, secPitchData, true);
        secPitchData->Norm();
//        freev(pitchCutted);
*/
        freeSimpleGraphData(dataSec);
        qDebug() << "New Data Processed";
    }
}


