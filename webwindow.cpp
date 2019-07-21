#include "webwindow.h"
#include "mainwindow.h"
#include "ui_webwindow.h"
#include "qdebug.h"

#include "drawer.h"
#include "drawerdp.h"
#include "settingsdialog.h"
#include "utils.h"

#include <QDir>
#include <QDirIterator>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QSettings>
#include <QWebEngineView>
#include <QWebChannel>

//class WebClass : public QObject
//{
//    Q_OBJECT
//    public slots:
//    void show_settings()
//    {
//        emit this->show_settings_signal();
//    }

//    signals:
//    void show_settings_signal();
//};

void checkLogFile()
{
    QFileInfo info1(LOG_FILE_NAME);
    if (info1.size() > LAG_FILE_MAX_SIZE)
    {
        QFile::remove(LOG_FILE_NAME);
    }
}

WebWindow::WebWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebWindow)
{
    ui->setupUi(this);
    this->initWeb();
    this->mainWindow = new MainWindow(this);

    checkLogFile();

    qDebug() << " Start application" << LOG_DATA;
}

WebWindow::~WebWindow()
{
    delete ui;
}

void WebWindow::attachObject()
{
    //QWebFrame * frame = this->ui->webView->page()->mainFrame();
    //frame->addToJavaScriptWindowObject( QString("api"), this );
}

bool WebWindow::isShowA0()
{
    SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();
    return sptk_settings->dp->showA0;
}

bool WebWindow::isShowF0()
{
    SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();
    return sptk_settings->dp->showF0;
}

bool WebWindow::isShowError()
{
    SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();
    return sptk_settings->dp->showError;
}

bool WebWindow::isShowTime()
{
    SPTK_SETTINGS * sptk_settings = SettingsDialog::getSPTKsettings();
    return sptk_settings->dp->showTime;
}

void WebWindow::setShowA0(QVariant value)
{
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationDirPath());
    settings.setValue("dp/showA0", value.toBool());
    qDebug() << "setShowA0 " << value.toBool() << LOG_DATA;
}

void WebWindow::setShowF0(QVariant value)
{
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationDirPath());
    settings.setValue("dp/showF0", value.toBool());
    qDebug() << "setShowF0 " << value.toBool() << LOG_DATA;
}

void WebWindow::setShowError(QVariant value)
{
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationDirPath());
    settings.setValue("dp/showError", value.toBool());
    qDebug() << "setShowError " << value.toBool() << LOG_DATA;
}

void WebWindow::setShowTime(QVariant value)
{
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationDirPath());
    settings.setValue("dp/showTime", value.toBool());
    qDebug() << "setShowTime " << value.toBool() << LOG_DATA;
}

QString WebWindow::getFiles()
{
    QStringList files = scanDirItems(QApplication::applicationDirPath() + DATA_PATH_TRAINING, WAVE_TYPE, QApplication::applicationDirPath() + DATA_PATH);
    files.sort();
    QString lastPath = "";

    QJsonArray jResult;
    QJsonObject jSection;
    QJsonArray jList;
    for(int i=0; i<files.size();i++)
    {
        QString file = files.at(i);
        int lastIndex = file.lastIndexOf("/");
        int firstIndex = file.indexOf("/", 1);

        QString filePath = file.left(lastIndex).replace("/", " ");
        QString fileTitle = filePath.mid(firstIndex).replace("/", " ");
        QString fileName = file.mid(lastIndex).replace("/", " ");

        if (lastPath == "") lastPath = fileTitle;

        if (lastPath != fileTitle)
        {
            jSection["title"] = lastPath;
            jSection["files"] = jList;
            jResult.append(jSection);

            QJsonObject jNewSection;
            jSection = jNewSection;
            lastPath = fileTitle;
            QJsonArray jNewList;
            jList = jNewList;
        }

        QJsonObject jItem;
        jItem["title"] = fileName;
        jItem["text"] = fileName;
        jItem["path"] = file;
        jList.append(jItem);
    }
    jSection["title"] = lastPath;
    jSection["files"] = jList;
    jResult.append(jSection);

    QJsonDocument jDoc(jResult);
    return QString(jDoc.toJson(QJsonDocument::Compact));
}

void WebWindow::initWeb()
{
    QWebEngineView *webView = new QWebEngineView;
    this->ui->verticalLayout->addWidget(webView);

    qDebug() << (QApplication::applicationDirPath() + "/html/index.html") << LOG_DATA;
    webView->load(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/html/index.html"));

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject("jshelper", this);
    webView->page()->setWebChannel(channel);
}

void WebWindow::showSettings() {
    this->mainWindow->settingsShow();
}

void WebWindow::openFile(QVariant url) {
    this->mainWindow->evaluation(url.toUrl().path(), new DrawerDP());
}

void WebWindow::playFile(QVariant url) {
    this->mainWindow->playRecord(url.toUrl().path());
}

void WebWindow::openApp() {
    this->mainWindow->show();
}
