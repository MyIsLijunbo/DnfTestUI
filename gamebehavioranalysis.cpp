#include "gamebehavioranalysis.h"

GameBehaviorAnalysis::GameBehaviorAnalysis(QObject *parent)
    : QObject{parent}
    , playerEntryLastPoint(0,0)
{

}

QPoint GameBehaviorAnalysis::PlayerMoveToEntry(const QPoint &play, const QPoint &entry)
{
    int playX = play.x() + 30;
    int playY = play.y() + 50;
    int entryX = entry.x() + 30;
    int entryY = entry.y() + 50;

    QPoint move(0,0);
    if (abs(entryX - playX) > 20)
    {
        move.setX(entryX - playX);
    }
    if (abs(entryY - playY) > 20)
    {
        move.setY(entryY - playY);
    }
    return move;
}

QPoint GameBehaviorAnalysis::PlayerEntryBehaviorAnalysis(const QPoint &play, const QPoint &entry)
{
    QPoint result = PlayerMoveToEntry(play, entry);


    if (0 == playerEntryLastPoint.x() && 0 == playerEntryLastPoint.y())
    {

    } else if ( abs(playerEntryLastPoint.x() - play.x()) == 0)
    {
        result.setX(0);
    }else if ( abs(playerEntryLastPoint.y() - play.y()) == 0)
    {
        result.setY(0);
    }

    playerEntryLastPoint.setX(play.x());
    playerEntryLastPoint.setY(play.y());
    return result;
}
