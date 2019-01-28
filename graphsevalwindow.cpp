#include "graphsevalwindow.h"
#include "ui_graphswindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

#include "graphswindow.h"

#include "drawerdp.h"
#include "soundplayer.h"
#include "settingsdialog.h"

#include "xlsxdocument.h"

#include <QSettings>

extern "C" {
    #include "./analysis/metrics.h"
}

GraphsEvalWindow::GraphsEvalWindow(QString path, Drawer * drawer, QWidget *parent) :
    GraphsWindow(parent)
{
    this->templatePath = path;
    this->path = path;
    this->drawer = drawer;
    this->QMGL->setDraw(this->drawer);
    this->drawFile(path);
    this->ui->playTemplateBtn->hide();
    this->ui->saveMetrics->hide();
    this->ui->openMetrics->hide();
    connect(this->ui->playTemplateBtn, SIGNAL(clicked()), this, SLOT(playTemplate()));
    connect(this->ui->showUMP, SIGNAL(clicked()), this, SLOT(showUMP()));
    connect(this->ui->saveMetrics, SIGNAL(clicked()), this, SLOT(saveMetrics()));
    connect(this->ui->openMetrics, SIGNAL(clicked()), this, SLOT(openMetrics()));


    SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();

    this->drawer->showUMP = sptk_settings->dp->showPortr;
    if(this->drawer->showUMP)
        this->ui->showUMP->setText("Show original");
    else
        this->ui->showUMP->setText("Show Universal Melodic Portrait (UMP)");
}

GraphsEvalWindow::~GraphsEvalWindow()
{

}

Drawer * GraphsEvalWindow::createNewDrawer(QString path)
{
    this->ui->saveMetrics->show();
    this->ui->playTemplateBtn->show();
    this->drawer->Proc(path);
    this->path = path;

    this->ui->totalC->setText(QString::number(this->drawer->proximity_curve_correlation));
    this->ui->totalI->setText(QString::number(this->drawer->proximity_curve_integral));
    this->ui->totalL->setText(QString::number(this->drawer->proximity_curve_local));
    this->ui->totalA->setText(QString::number(this->drawer->proximity_average));
    this->ui->totalPr->setText(QString::number(this->drawer->proximity_range));

    SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();

    switch (sptk_settings->dp->errorType) {
    case 0:
        this->ui->totalC->setStyleSheet("font-weight: bold");
        this->ui->totalCtitle->setStyleSheet("font-weight: bold");
        break;
    case 1:
        this->ui->totalI->setStyleSheet("font-weight: bold");
        this->ui->totalItitle->setStyleSheet("font-weight: bold");
        break;
    case 2:
        this->ui->totalL->setStyleSheet("font-weight: bold");
        this->ui->totalLtitle->setStyleSheet("font-weight: bold");
        break;
    case 3:
        this->ui->totalA->setStyleSheet("font-weight: bold");
        this->ui->totalAtitle->setStyleSheet("font-weight: bold");
        break;
    default:
        break;
    }

    return this->drawer;
}

void GraphsEvalWindow::playTemplate()
{
    SoundPlayer * player = new SoundPlayer(templatePath);
    player->start();
}

void GraphsEvalWindow::showUMP()
{
    if(this->drawer->showUMP)
        this->ui->showUMP->setText("Show Universal Melodic Portrait (UMP)");
    else
        this->ui->showUMP->setText("Show original");
    this->drawer->showUMP = !this->drawer->showUMP;
    this->QMGL->update();
}

void GraphsEvalWindow::saveMetrics()
{
    qDebug() << "saveMetrics" << LOG_DATA;

    QXlsx::Document xlsx;

    QXlsx::Format format_value;
    format_value.setHorizontalAlignment(QXlsx::Format::AlignLeft);

    QXlsx::Format format_title;
    format_title.setFontBold(true);
    format_title.setFontUnderline(QXlsx::Format::FontUnderlineSingle);

    QXlsx::Format format_subtitle;
    format_subtitle.setFontBold(true);
    format_subtitle.setVerticalAlignment(QXlsx::Format::AlignTop);

    QXlsx::Format format_file_subtitle;
    format_file_subtitle.setVerticalAlignment(QXlsx::Format::AlignTop);
    format_file_subtitle.setFontItalic(true);
    format_file_subtitle.setTextWarp(true);

    xlsx.setColumnWidth(1, 40);
    xlsx.setColumnWidth(2, 20);
    xlsx.setColumnWidth(3, 20);
    xlsx.mergeCells(QXlsx::CellRange(1,2,1,6));
    xlsx.mergeCells(QXlsx::CellRange(2,2,2,6));
    xlsx.setRowHeight(1, 50);
    xlsx.setRowHeight(2, 50);

    int row = 1;
    xlsx.write(row,   1, "Template", format_subtitle);
    xlsx.write(row++, 2, this->templatePath, format_file_subtitle);
    xlsx.write(row,   1, "Record", format_subtitle);
    xlsx.write(row++, 2, this->path, format_file_subtitle);

    MetricsData data = this->drawer->getMetricData();

    row++;
    xlsx.write(row,   1, "The data on the proximity", format_title);
    xlsx.write(row,   2, "Proximity", format_title);
    xlsx.write(row++, 3, "Distance", format_title);
    xlsx.write(row,   1, "Proximity curve correlation", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_PROXIMITY_CURVE_CORRELATION), format_value);
    xlsx.write(row++, 3, 100.0 - getMetric(data, METRIC_PROXIMITY_CURVE_CORRELATION), format_value);
    xlsx.write(row,   1, "Proximity curve integral", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_PROXIMITY_CURVE_INTEGRAL), format_value);
    xlsx.write(row++, 3, 100.0 - getMetric(data, METRIC_PROXIMITY_CURVE_INTEGRAL), format_value);
    xlsx.write(row,   1, "Proximity curve local", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_PROXIMITY_CURVE_LOCAL), format_value);
    xlsx.write(row++, 3, 100.0 - getMetric(data, METRIC_PROXIMITY_CURVE_LOCAL), format_value);
    xlsx.write(row,   1, "Average data on the proximity of curves", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_PROXIMITY_AVERAGE), format_value);
    xlsx.write(row++, 3, 100.0 - getMetric(data, METRIC_PROXIMITY_AVERAGE), format_value);
    xlsx.write(row,   1, "Proximity range", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_PROXIMITY_RANGE), format_value);
    xlsx.write(row++, 3, 100.0 - getMetric(data, METRIC_PROXIMITY_RANGE), format_value);

    row++;
    xlsx.write(row++, 1, "Reference data on templates and records", format_title);
    xlsx.write(row,   1, "F0 max - Template", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_TEMPLATE_F0_MAX), format_value);
    xlsx.write(row,   1, "F0 min - Template", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_TEMPLATE_F0_MIN), format_value);
    xlsx.write(row,   1, "F0 max - Recorded", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_RECORD_F0_MAX), format_value);
    xlsx.write(row,   1, "F0 min - Recorded", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_RECORD_F0_MIN), format_value);
    xlsx.write(row,   1, "Mean Value UMP - Recorded", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_MEAN_VALUE_UMP_RECORDED), format_value);
    xlsx.write(row,   1, "Mean Value UMP - Template", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_MEAN_VALUE_UMP_TEMPLATE), format_value);
    xlsx.write(row,   1, "Center of Gravity UMP - Recorded", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_CENTER_GRAVITY_UMP_RECORDED), format_value);
    xlsx.write(row,   1, "Center of Gravity UMP- Template", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_CENTER_GRAVITY_UMP_TEMPLATE), format_value);
    xlsx.write(row,   1, "Voiced Souds Level - Recorded", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_MEAN_VOLUME_RECORDED), format_value);
    xlsx.write(row,   1, "Voiced Sounds Level - Template", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_MEAN_VOLUME_TEMPLATE), format_value);
    xlsx.write(row,   1, "Voiced Sounds Duration - Recorded", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_TEMPO_RECORDED), format_value);
    xlsx.write(row,   1, "Voiced Sounds Duration - Template", format_subtitle);
    xlsx.write(row++, 2, getMetric(data, METRIC_TEMPO_TEMPLATE), format_value);

    row++;
    xlsx.write(row,   1, "Relative data on templates and records", format_title);
    xlsx.write(row,   2, "Relation", format_title);
    xlsx.write(row++, 3, "Difference", format_title);
    xlsx.write(row,   1, "Relative Diapason F0", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_RELATIVE_DIAPASON_F0), format_value);
    xlsx.write(row++, 3, getMetric(data, METRIC_RELATIVE_DIAPASON_F0) - 100.0, format_value);
    xlsx.write(row,   1, "Relative Register F0", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_RELATIVE_REGISTER_F0), format_value);
    xlsx.write(row++, 3, getMetric(data, METRIC_RELATIVE_REGISTER_F0) - 100.0, format_value);
    xlsx.write(row,   1, "Relative Center of Gravity UMP", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_RELATIVE_CENTER_GRAVITY_UMP), format_value);
    xlsx.write(row++, 3, getMetric(data, METRIC_RELATIVE_CENTER_GRAVITY_UMP) - 100.0, format_value);
    xlsx.write(row,   1, "Relative Mean Value UMP", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_RELATIVE_MEAN_UMP), format_value);
    xlsx.write(row++, 3, getMetric(data, METRIC_RELATIVE_MEAN_UMP) - 100.0, format_value);
    xlsx.write(row,   1, "Relative Voiced Souds Level", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_RELATEVE_MEAN_VOLUME), format_value);
    xlsx.write(row++, 3, getMetric(data, METRIC_RELATEVE_MEAN_VOLUME) - 100.0, format_value);
    xlsx.write(row,   1, "Relative Voiced Sounds Duration", format_subtitle);
    xlsx.write(row,   2, getMetric(data, METRIC_RELATIVE_TEMPO), format_value);
    xlsx.write(row++, 3, getMetric(data, METRIC_RELATIVE_TEMPO) - 100.0, format_value);

    QDir templateDir(this->templatePath);
    QString templateName = templateDir.dirName().remove(".wav", Qt::CaseInsensitive);
    QString recordName = QDir(this->path).dirName().remove(".wav", Qt::CaseInsensitive);
    QString fileName  = templateName + " - " + recordName + ".xlsx";

    templateDir.cdUp();
    this->metricsFilePath = templateDir.absoluteFilePath(fileName);
    qDebug() << "save to" << this->metricsFilePath;

    bool isOk = xlsx.saveAs(this->metricsFilePath);

    if (isOk)
    {
        this->ui->openMetrics->show();
    }
}

void GraphsEvalWindow::openMetrics()
{
    QDesktopServices::openUrl(QUrl("file:///" + this->metricsFilePath, QUrl::TolerantMode));
}

