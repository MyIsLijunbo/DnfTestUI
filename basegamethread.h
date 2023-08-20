#ifndef BASEGAMETHREAD_H
#define BASEGAMETHREAD_H
#include <QObject>
#include <QPointer>

#include "applicationcontrol.h"
#include "easytemplate.h"
#include "gamebehavioranalysis.h"
#include "player.h"
#include "screencapturewin.h"

class BaseGameThread : public QObject
{
    Q_OBJECT
public:
    explicit BaseGameThread(QObject *parent=nullptr)
        :QObject(parent)
    {}
public slots:
    virtual void startWorkInAThread() = 0;
};

class DnfThread : public BaseGameThread
{
    Q_OBJECT
public:
    explicit DnfThread(QObject *parent=nullptr);
public slots:
    virtual void startWorkInAThread();
    void timeTask();
private slots:
    void getPhotos(const QString path);
private:
    QPointer<ApplicationControl> application_;
    QPointer<Player> player_;
    QPointer<GameBehaviorAnalysis> behaviorAnalysis_;
    QPointer<ScreenCaptureWin> screenCaptureWin_;
    EasyTemplate picture_;
signals:
    void GetPhotosPath(const QString path);
    void SendMessageBox(const QString path);
};
#endif // BASEGAMETHREAD_H
