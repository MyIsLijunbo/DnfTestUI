#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
    , peripheralControl_(new PeripheralControl)
{

}

bool Player::InsertPlayerEvent(const int type, const int code, const int state, const int count)
{
    switch (type) {
    case 0:
        peripheralControl_->InsertKeyBoard(code,state,count);
        break;
    case 1:
        break;
    default:
        break;
    }

    return true;
}

void Player::Play()
{
    peripheralControl_->RunScript();
}

void Player::PlayOver()
{

}
