#ifndef SCREENCAPTUREWIN_H
#define SCREENCAPTUREWIN_H

#include <QObject>

class ScreenCaptureWin : public QObject
{
    Q_OBJECT
public:
    explicit ScreenCaptureWin(QObject *parent = nullptr);

    void ScreenCapture(QString &path);
signals:

};

#endif // SCREENCAPTUREWIN_H
