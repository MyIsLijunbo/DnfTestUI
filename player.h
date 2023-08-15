#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPointer>
#include "peripheralcontrol.h"
class Player : public QObject
{
    Q_OBJECT
public:
    enum {PlayerRun,PlayerStop};
    explicit Player(QObject *parent = nullptr);

    QPointer<PeripheralControl> peripheralControl_;

    bool InsertPlayerEvent(const int type,const int code, const int state, const int count);
    void Play();
    void PlayOver();
signals:

};

#endif // PLAYER_H
