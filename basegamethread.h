#ifndef BASEGAMETHREAD_H
#define BASEGAMETHREAD_H
#include <QObject>
#include <QPointer>

#include "applicationcontrol.h"
#include "easytemplate.h"
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
public:
    explicit DnfThread(QObject *parent=nullptr);
public slots:
    virtual void startWorkInAThread();
private slots:
    void getPhotos(const QString path);
private:
    QPointer<ApplicationControl> application_;
    EasyTemplate picture_;

signals:
    void GetPhotos(const QString path);
};
#endif // BASEGAMETHREAD_H
