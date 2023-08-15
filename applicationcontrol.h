#ifndef APPLICATIONCONTROL_H
#define APPLICATIONCONTROL_H

#include <QObject>
#include <Windows.h>
class ApplicationControl : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationControl(QObject *parent = nullptr);

    bool ShowApplication(const QString &name);
signals:
private:
    HWND handle_;
};

#endif // APPLICATIONCONTROL_H
