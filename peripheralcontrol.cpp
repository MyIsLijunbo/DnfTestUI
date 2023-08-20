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
    Sleep(20);

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        qDebug()<< "SendInput failed: 0x%x\n"<< HRESULT_FROM_WIN32(GetLastError());
        return 0;
    }
    else
    {
        printKeyBoardEntry(VirtualKey, keyState);
        return 1;
    }
}

bool PeripheralControl::MouseEvent(const int dx, const int dy, const bool absolute)
{
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//获取屏幕分辨率宽度
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//获取屏幕分辨率高度
    double fx = dx*(65535.0f / fScreenWidth);
    double fy = dy*(65535.0f / fScreenHeight);

    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dx = fx;
    inputs[0].mi.dy = fy;
    inputs[0].mi.mouseData = 0;
    if (absolute == 1)
    {
        inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    }
    else if (absolute == 0)
    {
        inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    }


    Sleep(20);
    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        qDebug() << "SendInput failed: 0x%x\n" << HRESULT_FROM_WIN32(GetLastError());
        return 0;
    }
    else
    {
        qDebug() << "mouse Success" ;
        return 1;
    }

}
void PeripheralControl::MouseLeftDown()//鼠标左键按下
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    Sleep(10);
    SendInput(1, &Input, sizeof(INPUT));
}

void PeripheralControl::MouseLeftUp()//鼠标左键放开
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    Sleep(10);
    SendInput(1, &Input, sizeof(INPUT));
}

void PeripheralControl::MouseRightDown()
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    Sleep(10);
    SendInput(1, &Input, sizeof(INPUT));
}

void PeripheralControl::MouseRightUp()
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    Sleep(10);
    SendInput(1, &Input, sizeof(INPUT));
}

bool PeripheralControl::MouseLeftClick(const int dx, const int dy, const int once)
{
    for(int i = 0; i < once; i++)
    {
         bool succ = MouseEvent(dx, dy, true);
         if (!succ)
         {
             return succ;
         }
        MouseLeftDown();
        MouseLeftUp();
    }
     return true;
}

bool PeripheralControl::MouseRightClick(const int dx, const int dy, const int once)
{
    for(int i = 0; i < once; i++)
    {
         bool succ = MouseEvent(dx, dy, true);
         if (!succ)
         {
             return succ;
         }
        MouseRightDown();
        MouseRightUp();
    }
    return true;
}

void PeripheralControl::RunScript()
{
    QMapIterator<quint64,KeyBoardInfo> i(periheralEventMap_);
    ClearkeyBoardDownEvent();
    while (i.hasNext()) {
        i.next();
        auto value = i.value();
        for (quint32 i = 0; i <  value.count; i++) {
            if (KeyBoardDownUp == value.keyState)
            {
                KeyBoardEvent(value.keyCode, KeyBordDown);
                KeyBoardEvent(value.keyCode, KeyBordUp);
            }else
            {
                lastKeyBoradCode = value.keyCode;
                KeyBoardEvent(value.keyCode, value.keyState);
            }
        }
    }
}

void PeripheralControl::ClearScript()
{
    ClearkeyBoardDownEvent();
    periheralEventMap_.clear();
}

void PeripheralControl::ClearkeyBoardDownEvent()
{

}

void PeripheralControl::InsertKeyBoard(const quint64 keyCode, const quint8 keyState, const quint32 count)
{
    if (keyCode == (quint64)lastKeyBoradCode && KeyBordDown == keyState)
    {
        return;
    }else if (0 != lastKeyBoradCode && lastKeyBoradCode != keyCode && KeyBordDown == keyState)
    {
        KeyBoardEvent(lastKeyBoradCode, KeyBordUp);
    }

    static quint64 eventIndex = 0;
    periheralEventMap_[eventIndex].keyState = keyState;
    periheralEventMap_[eventIndex].keyCode = keyCode;
    periheralEventMap_[eventIndex].count = count;
    ++eventIndex;
}
void PeripheralControl::printKeyBoardEntry(const int code, const int state) const
{
    QString strState;
    if (KeyBordUp == state)
    {
        strState = " 弹起";
    }else
    {
        strState = " 按下";
    }

    switch (code) {
    case 0x30: case 0x60:
        qDebug()<<"检测到按键："<< "0" << strState;
        break;
    case 0x31: case 0x61:
        qDebug()<<"检测到按键："<< "1" << strState;
        break;
    case 0x32: case 0x62:
        qDebug()<<"检测到按键："<< "2" << strState;
        break;
    case 0x33: case 0x63:
        qDebug()<< "检测到按键："<< "3" << strState;
        break;
    case 0x34: case 0x64:
        qDebug()<< "检测到按键："<< "4" << strState;
        break;
    case 0x35: case 0x65:
        qDebug()<< "检测到按键："<< "5" << strState;
        break;
    case 0x36: case 0x66:
        qDebug()<< "检测到按键："<< "6" << strState;
        break;
    case 0x37: case 0x67:
        qDebug()<< "检测到按键："<< "7" << strState;
        break;
    case 0x38: case 0x68:
        qDebug()<< "检测到按键："<< "8" << strState;
        break;
    case 0x39: case 0x69:
        qDebug()<< "检测到按键："<< "9" << strState;
        break;
    case 0x41:
        qDebug()<< "检测到按键："<< "A" << strState;
        break;
    case 0x42:
        qDebug()<< "检测到按键："<< "B" << strState;
        break;
    case 0x43:
        qDebug()<< "检测到按键："<< "C" << strState;
        break;
    case 0x44:
        qDebug()<< "检测到按键："<< "D" << strState;
        break;
    case 0x45:
        qDebug()<< "检测到按键："<< "E" << strState;
        break;
    case 0x46:
        qDebug()<< "检测到按键："<< "F" << strState;
        break;
    case 0x47:
        qDebug()<< "检测到按键："<< "G" << strState;
        break;
    case 0x48:
        qDebug()<< "检测到按键："<< "H" << strState;
        break;
    case 0x49:
        qDebug()<< "检测到按键："<< "I" << strState;
        break;
    case 0x4A:
        qDebug()<< "检测到按键："<< "J" << strState;
        break;
    case 0x4B:
        qDebug()<< "检测到按键："<< "K" << strState;
        break;
    case 0x4C:
        qDebug()<< "检测到按键："<< "L" << strState;
        break;
    case 0x4D:
        qDebug()<< "检测到按键："<< "M" << strState;
        break;
    case 0x4E:
        qDebug()<< "检测到按键："<< "N" << strState;
        break;
    case 0x4F:
        qDebug()<< "检测到按键："<< "O" << strState;
        break;
    case 0x50:
        qDebug()<< "检测到按键："<< "P" << strState;
        break;
    case 0x51:
        qDebug()<< "检测到按键："<< "Q" << strState;
        break;
    case 0x52:
        qDebug()<< "检测到按键："<< "R" << strState;
        break;
    case 0x53:
        qDebug()<< "检测到按键："<< "S" << strState;
        break;
    case 0x54:
        qDebug()<< "检测到按键："<< "T" << strState;
        break;
    case 0x55:
        qDebug()<< "检测到按键："<< "U" << strState;
        break;
    case 0x56:
        qDebug()<< "检测到按键："<< "V" << strState;
        break;
    case 0x57:
        qDebug()<< "检测到按键："<< "W" << strState;
        break;
    case 0x58:
        qDebug()<< "检测到按键："<< "X" << strState;
        break;
    case 0x59:
        qDebug()<< "检测到按键："<< "Y" << strState;
        break;
    case 0x5A:
        qDebug()<< "检测到按键："<< "Z" << strState;
        break;
    case 0x6A:
        qDebug()<< "检测到按键："<< "*" << strState;
        break;
    case 0x6B:
        qDebug()<< "检测到按键："<< "+" << strState;
        break;
    case 0x6D:
        qDebug()<< "检测到按键："<< "-" << strState;
        break;
    case 0x6E:
        qDebug()<< "检测到按键："<< "." << strState;
        break;
    case 0x6F:
        qDebug()<< "检测到按键："<< "/" << strState;
        break;
    case 0x0D:
        qDebug()<< "检测到按键："<< "Enter" << strState;
        break;
    case 0xA0: case 0xA1:
        qDebug()<< "检测到按键："<< "Shift" << strState;
        break;
    case 0x08:
        qDebug()<< "检测到按键："<< "Backspace" << strState;
        break;
    case 0x20:
        qDebug()<< "检测到按键："<< "Space" << strState;
        break;
    }
}

quint8 PeripheralControl::scanCodeFunc(const quint64 pKey)
{
    const int result = MapVirtualKey(pKey, MAPVK_VK_TO_VSC);
    return static_cast<BYTE>(result);
}
