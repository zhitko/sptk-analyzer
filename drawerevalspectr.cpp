#include "drawerevalspectr.h"

#include "drawerevalpitch.h"

#include <QFile>
#include <QDebug>

#include "settingsdialog.h"

#include "DP/vectordp.h"
#include "DP/spectrdp.h"

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

DrawerEvalSpectr::DrawerEvalSpectr() :
    Drawer(),
    secFileName(""),
    result(0),
    first(true)
{
    secWaveData = NULL;
    secSpecData = NULL;
    secSpecDataOrig = NULL;
}

DrawerEvalSpectr::~DrawerEvalSpectr()
{
    qDebug() << "DrawerEval removed";
    if (secWaveData) delete secWaveData;
    if (secSpecData) delete secSpecData;
    if (secSpecDataOrig) delete secSpecDataOrig;
}

int DrawerEvalSpectr::Draw(mglGraph *gr)
{
    qDebug() << "start drawing";

    gr->DefaultPlotParam();
    gr->Clf();

    qDebug() << "waveData";
    gr->MultiPlot(1, 23, 0, 1, 1, "#");
    gr->SetRange('y', 0, 1);
    gr->Plot(*waveData, "-B");
    gr->Plot(*pWaveData, "-y1");
    gr->Plot(*nWaveData, "-q1");
    gr->Plot(*tWaveData, "-c1");

    specData->Norm(0, 1);
    gr->MultiPlot(1, 23, 4, 1, 6, "#");
    if(stereo) gr->Rotate(50,60);
    QString colors = QString("w{w,%1}k").arg(QString::number(0));
    gr->SetDefScheme(colors.toStdString().c_str());
    gr->Surf(*specData);

    if(!this->secFileName.isEmpty()){
        qDebug() << "secWaveData";
        gr->MultiPlot(1, 23, 1, 1, 1, "#");
        gr->SetRange('y', 0, 1);
        gr->Plot(*secWaveData, "B");

        gr->MultiPlot(1, 23, 3, 1, 1, "#");
        gr->Puts(mglPoint(0,0),QString("Your score: \\big{#r{%1}}").arg(this->result).toUtf8().data(), ":C", 50);

        secSpecDataOrig->Norm(0, 1);
        gr->MultiPlot(1, 23, 11, 1, 6, "#");
        if(stereo) gr->Rotate(50,60);
        gr->SetDefScheme(colors.toStdString().c_str());
        gr->Surf(*secSpecDataOrig);

        secSpecData->Norm(0, 1);
        gr->MultiPlot(1, 23, 17, 1, 6, "#");
        if(stereo) gr->Rotate(50,60);
        gr->SetDefScheme(colors.toStdString().c_str());
        gr->Surf(*secSpecData);
    }

    qDebug() << "finish drawing";
    return 0;
}

void DrawerEvalSpectr::Proc(QString fname)
{
    if(first)
    {
        qDebug() << "Drawer::Proc";
        Drawer::Proc(fname);
        first = false;
    }
    else
    {
        MathGLSettings * mathgl_settings = SettingsDialog::getMathGLSettings();
        SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();

        qDebug() << "DrawerEval::Proc";
        this->secFileName = fname;

        GraphData dataSec = ProcWave2Data(this->secFileName);

        secWaveData = createMglData(dataSec.d_full_wave, secWaveData);
        qDebug() << "waveData New Filled";

        int speksize = sptk_settings->spec->leng / 2 + 1;
        int specX = dataSec.d_spec_proc.x/speksize;
        int specY = speksize;
        if (secSpecDataOrig) delete secSpecDataOrig;
        secSpecDataOrig = new mglData();
        secSpecDataOrig->Create(specX, specY);
        for(long j=0;j<specY;j++)
            for(long i=0;i<specX;i++)
            {
                long i0 = i+specX*j;
                long i1 = j+specY*i;
                secSpecDataOrig->a[i0] = dataSec.d_spec_proc.v[i1];
            }
        secSpecDataOrig->Squeeze(mathgl_settings->quality, 1);

        qDebug() << "Start DP";
        qDebug() << "globalLimit DP" << sptk_settings->dp->globalLimit;
        qDebug() << "localLimit DP" << sptk_settings->dp->localLimit;
        SpectrDP dp(new SpectrSignal(copyv(data->d_spec), speksize),
                    new SpectrSignal(copyv(dataSec.d_spec), speksize),
                    sptk_settings->dp->globalLimit,
                    sptk_settings->dp->localLimit
                    );
        vector newSpec = dp.getScaledSignal()->getArray();
        this->result = dp.getSignalMask()->value.globalError;
        qDebug() << "Stop DP";

        specX = newSpec.x/speksize;
        specY = speksize;
        if (secSpecData) delete secSpecData;
        secSpecData = new mglData();
        secSpecData->Create(specX, specY);
        for(long j=0;j<specY;j++)
            for(long i=0;i<specX;i++)
            {
                long i0 = i+specX*j;
                long i1 = j+specY*i;
                secSpecData->a[i0] = newSpec.v[i1];
            }
        secSpecData->Squeeze(mathgl_settings->quality, 1);

        freeGraphData(dataSec);
        qDebug() << "New Data Processed";
    }
}
