#ifndef SCREENCAPTUREWIN_H
#define SCREENCAPTUREWIN_H

#include <QObject>
#include<windows.h>
#include <QRect>
class ScreenCaptureWin : public QObject
{
    Q_OBJECT
public:
    explicit ScreenCaptureWin(QObject *parent = nullptr);

    QRect ScreenCapture(HWND handle,QString &path);
signals:

};

#endif // SCREENCAPTUREWIN_H
