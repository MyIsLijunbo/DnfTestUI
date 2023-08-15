#include "peripheralcontrol.h"
#include <Windows.h>
#include <QDebug>

PeripheralControl::PeripheralControl(QObject *parent)
    : QObject{parent}
{

}

bool PeripheralControl::KeyBoardEvent(const quint64 VirtualKey, const quint8 keyState)
{
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VirtualKey;
    inputs[0].ki.wScan = static_cast<WORD>(scanCodeFunc(VirtualKey));
    if (keyState == KeyBordDown)
    {

    }
    else if (keyState == KeyBordUp)
    {
        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
    }
    Sleep(50);

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        qDebug()<< "SendInput failed: 0x%x\n"<< HRESULT_FROM_WIN32(GetLastError());
        return 0;
    }
    else
    {
        printKeyBoardEntry(VirtualKey);
        return 1;
    }
}

void PeripheralControl::RunScript()
{
    QMapIterator<quint64,KeyBoardInfo> i(periheralEventMap_);
    while (i.hasNext()) {
        i.next();
        auto value = i.value();
        for (int i = 0; i <  value.count; i++) {
            if (KeyBoardDownUp == value.keyState)
            {
                KeyBoardEvent(value.keyCode, KeyBordDown);
                KeyBoardEvent(value.keyCode, KeyBordUp);
            }else
            {
                KeyBoardEvent(value.keyCode, value.keyState);
            }
        }
    }
}

void PeripheralControl::ClearScript()
{
    periheralEventMap_.clear();
}

void PeripheralControl::InsertKeyBoard(const quint64 keyCode, const quint8 keyState, const quint32 count)
{
    static quint64 eventIndex = 0;
    periheralEventMap_[eventIndex].keyState = keyState;
    periheralEventMap_[eventIndex].keyCode = keyCode;
    periheralEventMap_[eventIndex].count = count;
    ++eventIndex;
}
void PeripheralControl::printKeyBoardEntry(int code)
{
    switch (code) {
    case 0x30: case 0x60:
        qDebug()<<"检测到按键："<< "0";
        break;
    case 0x31: case 0x61:
        qDebug()<<"检测到按键："<< "1";
        break;
    case 0x32: case 0x62:
        qDebug()<<"检测到按键："<< "2";
        break;
    case 0x33: case 0x63:
        qDebug()<< "检测到按键："<< "3";
        break;
    case 0x34: case 0x64:
        qDebug()<< "检测到按键："<< "4";
        break;
    case 0x35: case 0x65:
        qDebug()<< "检测到按键："<< "5";
        break;
    case 0x36: case 0x66:
        qDebug()<< "检测到按键："<< "6";
        break;
    case 0x37: case 0x67:
        qDebug()<< "检测到按键："<< "7";
        break;
    case 0x38: case 0x68:
        qDebug()<< "检测到按键："<< "8";
        break;
    case 0x39: case 0x69:
        qDebug()<< "检测到按键："<< "9";
        break;
    case 0x41:
        qDebug()<< "检测到按键："<< "A";
        break;
    case 0x42:
        qDebug()<< "检测到按键："<< "B";
        break;
    case 0x43:
        qDebug()<< "检测到按键："<< "C";
        break;
    case 0x44:
        qDebug()<< "检测到按键："<< "D";
        break;
    case 0x45:
        qDebug()<< "检测到按键："<< "E";
        break;
    case 0x46:
        qDebug()<< "检测到按键："<< "F";
        break;
    case 0x47:
        qDebug()<< "检测到按键："<< "G";
        break;
    case 0x48:
        qDebug()<< "检测到按键："<< "H";
        break;
    case 0x49:
        qDebug()<< "检测到按键："<< "I";
        break;
    case 0x4A:
        qDebug()<< "检测到按键："<< "J";
        break;
    case 0x4B:
        qDebug()<< "检测到按键："<< "K";
        break;
    case 0x4C:
        qDebug()<< "检测到按键："<< "L";
        break;
    case 0x4D:
        qDebug()<< "检测到按键："<< "M";
        break;
    case 0x4E:
        qDebug()<< "检测到按键："<< "N";
        break;
    case 0x4F:
        qDebug()<< "检测到按键："<< "O";
        break;
    case 0x50:
        qDebug()<< "检测到按键："<< "P";
        break;
    case 0x51:
        qDebug()<< "检测到按键："<< "Q";
        break;
    case 0x52:
        qDebug()<< "检测到按键："<< "R";
        break;
    case 0x53:
        qDebug()<< "检测到按键："<< "S";
        break;
    case 0x54:
        qDebug()<< "检测到按键："<< "T";
        break;
    case 0x55:
        qDebug()<< "检测到按键："<< "U";
        break;
    case 0x56:
        qDebug()<< "检测到按键："<< "V";
        break;
    case 0x57:
        qDebug()<< "检测到按键："<< "W";
        break;
    case 0x58:
        qDebug()<< "检测到按键："<< "X";
        break;
    case 0x59:
        qDebug()<< "检测到按键："<< "Y";
        break;
    case 0x5A:
        qDebug()<< "检测到按键："<< "Z";
        break;
    case 0x6A:
        qDebug()<< "检测到按键："<< "*";
        break;
    case 0x6B:
        qDebug()<< "检测到按键："<< "+";
        break;
    case 0x6D:
        qDebug()<< "检测到按键："<< "-";
        break;
    case 0x6E:
        qDebug()<< "检测到按键："<< ".";
        break;
    case 0x6F:
        qDebug()<< "检测到按键："<< "/";
        break;
    case 0x0D:
        qDebug()<< "检测到按键："<< "Enter";
        break;
    case 0xA0: case 0xA1:
        qDebug()<< "检测到按键："<< "Shift";
        break;
    case 0x08:
        qDebug()<< "检测到按键："<< "Backspace";
        break;
    case 0x20:
        qDebug()<< "检测到按键："<< "Space";
        break;
    }
}

quint8 PeripheralControl::scanCodeFunc(const quint64 pKey)
{
    const int result = MapVirtualKey(pKey, MAPVK_VK_TO_VSC);
    return static_cast<BYTE>(result);
}
