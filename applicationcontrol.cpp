#include "applicationcontrol.h"
#include <QDebug>
ApplicationControl::ApplicationControl(QObject *parent)
    : QObject{parent}
{

}

bool ApplicationControl::ShowApplication(const QString &name)
{
    wchar_t namew[255] = {0};
    name.toWCharArray(namew);
    handle_ = FindWindow(NULL, namew);  //找到记事本窗口的句柄
    if (!handle_)
    {
        qDebug() << "not find handle! \n";
        return false;
    }
    else {
       // SetActiveWindow(handle_);
       // SetFocus(handle_);
        BOOL succ = SetForegroundWindow(handle_);
        if (!succ)
        {
            qDebug() << "not find handle! \n";
            return false;
        }
    }
    return true;
}
