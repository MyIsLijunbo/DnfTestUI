#ifndef PERIPHERALCONTROL_H
#define PERIPHERALCONTROL_H

#include <QMap>
#include <QObject>

// namespace name

struct KeyBoardInfo{
    quint8  peripheralType; // 0 表示键盘， 1表示鼠标 其他暂时未定义
    quint64 keyCode;
    quint8  keyState;
    quint32 count;
    KeyBoardInfo()
        : peripheralType(0)
        ,keyCode(0)
        , keyState(0)
        , count(0)
    {}
};
class PeripheralControl : public QObject
{
    Q_OBJECT
public:
    enum KeyBordState{KeyBoardDownUp,KeyBordDown,KeyBordUp};
    explicit PeripheralControl(QObject *parent = nullptr);
    bool KeyBoardEvent(const quint64 keyCode, const quint8 keyState);

    void InsertKeyBoard(const quint64 keyCode, const quint8 keyState, const quint32 count);

    void RunScript();
    void ClearScript();
    void ClearkeyBoardDownEvent();
signals:

private:
    void printKeyBoardEntry(const int code, const int state) const;
    quint8 scanCodeFunc(const quint64 pKey);
    QMap<quint64,KeyBoardInfo> periheralEventMap_;
    quint64 lastKeyBoradCode = 0;
};


#endif // PERIPHERALCONTROL_H
