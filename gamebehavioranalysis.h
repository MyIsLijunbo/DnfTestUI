#ifndef GAMEBEHAVIORANALYSIS_H
#define GAMEBEHAVIORANALYSIS_H

#include <QObject>
#include <QPoint>

class GameBehaviorAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit GameBehaviorAnalysis(QObject *parent = nullptr);

    QPoint PlayerMoveToEntry(const QPoint &play,const QPoint &entry);
    quint64 PlayerEntryBehaviorAnalysis(const QPoint &play,const QPoint &entry);
    quint64 keyBoardCode;
signals:

private:
    QPoint playerEntryLastPoint;

};

#endif // GAMEBEHAVIORANALYSIS_H
