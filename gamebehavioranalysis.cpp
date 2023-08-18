#include "gamebehavioranalysis.h"
#include "qdebug.h"
#include "GlobalValue.h"
#define PLAYER_MOVE_RAULT_TOLERANT 5

GameBehaviorAnalysis::GameBehaviorAnalysis(QObject *parent)
    : QObject{parent}
    , keyBoardCode(0)
    , playerEntryLastPoint(0,0)

{

}

QPoint GameBehaviorAnalysis::PlayerMoveToEntry(const QPoint &play, const QPoint &entry)
{
    int playX = play.x() + 51;
    int playY = play.y() + 100;
    int entryX = entry.x() + 14;
    int entryY = entry.y() + 38;

    QPoint move(0,0);
    if (abs(entryX - playX) > PLAYER_MOVE_RAULT_TOLERANT)
    {
        move.setX(entryX - playX);
    }
    if (abs(entryY - playY) > PLAYER_MOVE_RAULT_TOLERANT)
    {
        move.setY(entryY - playY);
    }
    return move;
}

quint64 GameBehaviorAnalysis::PlayerEntryBehaviorAnalysis(const QPoint &play, const QPoint &entry)
{
    QPoint result = PlayerMoveToEntry(play, entry);
    quint64 code = 0;

    if (0 == playerEntryLastPoint.x() && 0 == playerEntryLastPoint.y())
    {
        if (result.y() > 0 && result.y() > PLAYER_MOVE_RAULT_TOLERANT)
        {
            code =   VK_DOWN;
        }else if (result.y() < 0 && abs(result.y()) > PLAYER_MOVE_RAULT_TOLERANT)
        {
            code =  VK_UP;
        }else if (result.x() > 0 && result.x() > PLAYER_MOVE_RAULT_TOLERANT)
        {
            code =  VK_RIGHT;
        }else if (result.x() < 0 && abs(result.x()) > PLAYER_MOVE_RAULT_TOLERANT)
        {
            code =  VK_LEFT;
        }
    } else if ( abs(playerEntryLastPoint.x() - play.x()) == 0 && abs(playerEntryLastPoint.y() - play.y()) == 0)
    {
        if (result.y() > 0 && result.y() > PLAYER_MOVE_RAULT_TOLERANT && keyBoardCode != VK_DOWN)
        {
            code =   VK_DOWN;
        }else if (result.y() < 0 && abs(result.y()) > PLAYER_MOVE_RAULT_TOLERANT && keyBoardCode != VK_UP)
        {
            code =  VK_UP;
        }else if (result.x() > 0 && result.x() > PLAYER_MOVE_RAULT_TOLERANT && keyBoardCode != VK_RIGHT)
        {
            code =  VK_RIGHT;
        }else if (result.x() < 0 && abs(result.x()) > PLAYER_MOVE_RAULT_TOLERANT && keyBoardCode != VK_LEFT)
        {
            code =  VK_LEFT;
        }

    }

    qDebug()<< "上一次玩家位置: "<< playerEntryLastPoint.x() << " " << playerEntryLastPoint.y()<< " keyBoardCode :" << keyBoardCode;
    qDebug()<< "本次次玩家位置: "<< play.x() << " " << play.y()<< " Code :" << code;

    playerEntryLastPoint.setX(play.x());
    playerEntryLastPoint.setY(play.y());
    keyBoardCode = code;
    return keyBoardCode;
}
