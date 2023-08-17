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
    QPoint PlayerEntryBehaviorAnalysis(const QPoint &play,const QPoint &entry);
signals:

private:
    QPoint playerEntryLastPoint;
};

#endif // GAMEBEHAVIORANALYSIS_H
