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
    bool SetWindowPosion(const int x, const int y, const int width, const int height);
    void GetWindowPosion( int &x,  int &y,  int &width,  int &height);
    HWND handle_;
signals:
private:

};

#endif // APPLICATIONCONTROL_H
