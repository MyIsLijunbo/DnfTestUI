#include "mainwindow.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <vector>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

static QMutex mutex;
void customMessageHandler(QtMsgType type,
                          const QMessageLogContext &context,
                          const QString &msg)
{
    //Q_UNUSED(context)
    QDateTime _datetime = QDateTime::currentDateTime();
    QString szDate = _datetime.toString("yyyy-MM-dd hh:mm:ss.zzz");//"yyyy-MM-dd hh:mm:ss ddd"
    QString txt(szDate);

    switch (type)
    {
    case QtDebugMsg://调试信息提示
    {
        txt += QString(" [Debug] ");
        break;
    }
    case QtInfoMsg://信息输出
    {
        txt += QString(" [Info] ");
        break;
    }
    case QtWarningMsg://一般的warning提示
    {
        txt += QString(" [Warning] ");
        break;
    }
    case QtCriticalMsg://严重错误提示
    {
        txt += QString(" [Critical] ");
        break;
    }
    case QtFatalMsg://致命错误提示
    {
        txt += QString(" [Fatal] ");
        //abort();
        break;
    }
    default:
    {
        txt += QString(" [Trace] ");
        break;
    }
    }

    txt.append( QString(" %1").arg(context.file) );
    txt.append( QString("<%1>: ").arg(context.line) );
    txt.append(msg);

    mutex.lock();
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << txt << "\r\n";
    file.close();
    mutex.unlock();
}

void removeDebugFile()
{
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.remove();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册MessageHandler
    removeDebugFile();
    qInstallMessageHandler(customMessageHandler);

    MainWindow w;
    w.show();
    return a.exec();
}
