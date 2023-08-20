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

bool ApplicationControl::SetWindowPosion(const int x, const int y, const int width, const int height)
{
    if (!handle_)
    {
        qDebug() << "not find handle! \n";
        return false;
    }

    return MoveWindow(handle_, x, y, width, height, true);
}

void ApplicationControl::GetWindowPosion(int &x, int &y, int &width, int &height)
{
    if (!handle_)
    {
        qDebug() << "not find handle! \n";
        return ;
    }

    RECT rect;
    GetWindowRect(handle_,&rect);
    x = rect.top;
    y = rect.left;
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    return ;
}
