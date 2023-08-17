#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H
#include<QMap>
#define VK_UP 0x37
#define VK_DOWN 0x39
#define VK_LEFT 0x38
#define VK_RIGHT 0x30

//#define VK_UP 0x26
//#define VK_DOWN 0x28
//#define VK_LEFT 0x25
//#define VK_RIGHT 0x27
extern QString g_AppPath ;
extern QMap<QString, quint64> KeyBoardToCode_ ;

#endif // GLOBALVALUE_H
