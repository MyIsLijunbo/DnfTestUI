#include "screencapturewin.h"
#include "qdebug.h"

#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>
using namespace std;
#pragma comment(lib,"User32.lib");
#pragma comment(lib,"Gdi32.lib");
void Screenbmp(HWND hwnd, int left, int top, int width, int height, CHAR* path);
ScreenCaptureWin::ScreenCaptureWin(QObject *parent) : QObject(parent)
{

}

QRect ScreenCaptureWin::ScreenCapture(HWND handle,QString &path)
{
    RECT rect;
    GetWindowRect(handle,&rect);
    QRect resRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);

    // 保存整个屏幕为QPixmap
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    QPixmap pixmapCopy = pixmap.copy(resRect); // copy图片
    if(!pixmapCopy.save(path,"png"))
    {
        qDebug()<<"copy cut save png failed";
    }

    return resRect;
}


