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
//    if(!pixmap.save(path,"png"))
//    {
//        qDebug()<<"cut save png failed";
//    }


    QPixmap pixmapCopy = pixmap.copy(resRect); // copy图片
    if(!pixmapCopy.save(path,"png"))
    {
        qDebug()<<"copy cut save png failed";
    }

    return resRect;
}


//输入目标窗口的句柄、左上角的位置以及截图的长宽和保存地址
//void Screenbmp(HWND hwnd, int left, int top, int width, int height, CHAR* path)
//{
//    //1、获得指定窗口的dc（源dc）
//    //注意GetWindowDC会把窗口的标题栏也同时截图，如果不需要窗口的标题就使用GetDC(hwnd)
//    HDC sourceDC= GetWindowDC(hwnd);
//    //2、根据源dc创建兼容内存DC
//    HDC momDC;//内存DC
//    momDC = ::CreateCompatibleDC(sourceDC);
//    //3、根据源dc创建兼容位图
//    HBITMAP memBitmap;
//    memBitmap = ::CreateCompatibleBitmap(sourceDC, width, height);
//    //4、将兼容位图写入内存dc
//    SelectObject(momDC, memBitmap);
//    //5、截图
//    BitBlt(momDC, 0, 0, width, height, sourceDC, left, top, SRCCOPY);
//    //6、以下代码保存截图信息到文件中
//    //6.1获得位图信息
//    BITMAP bmp;
//    GetObject(memBitmap, sizeof(BITMAP), &bmp);
//    //6.2图片保存路径和方式
//    FILE* fp;
//    fopen_s(&fp, path, "w+b");
//    //6.3创建位图文件头
//    //位图文件头设置默认值为0
//    BITMAPFILEHEADER bfh = { 0 };
//    ////到位图数据的偏移量（此步骤固定，位图编译量即为位图文件头+位图信息头+调色板的大小，调色板设置为0）
//    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//    //文件总的大小
//    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;
//    //bfType固定为BM，(WORD)0x4d42表示为BM
//    bfh.bfType = (WORD)0x4d42;
//    //6.4创建文件信息头
//    //位图信息头，默认设置为0
//    BITMAPINFOHEADER bih = { 0 };
//    //每个像素字节大小
//    bih.biBitCount = bmp.bmBitsPixel;
//    bih.biCompression = BI_RGB;
//    //高度
//    bih.biHeight = bmp.bmHeight;
//    bih.biPlanes = 1;
//    bih.biSize = sizeof(BITMAPINFOHEADER);
//    //图像数据大小
//    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
//    //宽度
//    bih.biWidth = bmp.bmWidth;
//    //6.5写入位图文件头
//    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);
//    //6.6写入位图信息头
//    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
//    //6.7申请内存保存位图数据
//    BYTE *p = new BYTE[bmp.bmWidthBytes * bmp.bmHeight];
//    //6.8获取位图数据
//    GetDIBits(momDC, (HBITMAP)memBitmap, 0, height, p,
//              (LPBITMAPINFO)&bih, DIB_RGB_COLORS);
//    //6.9写入位图数据
//    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);
//    //6.10先删除开辟的内存，然后关闭文件
//    delete[] p;
//    fclose(fp);
//    //7删除链接
//    //7.1删除创建的位图
//    DeleteObject(memBitmap);
//    //7.2删除创建的兼容内存DC
//    DeleteDC(momDC);
//    //7.3#释放窗口DC
//    ReleaseDC(hwnd, sourceDC);
//}
