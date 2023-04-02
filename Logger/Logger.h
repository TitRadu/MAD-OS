#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED
#define INFOA "INFO"
#define DBGA "DBG"
#define WRNA "WRN"
#define ERRA "ERR"
#define INFOW L"INFO"
#define DBGW L"DBG"
#define WRNW L"WRN"
#define ERRW L"ERR"
#include <stdio.h>
#include <Windows.h>

PCSTR getDayA(WORD);
PCWSTR getDayW(WORD);
PCSTR getMonthA(WORD);
PCWSTR getMonthW(WORD);
void prepareLogFile();
void LogA(PCSTR, PCSTR, PCSTR, PCSTR);
void LogW(PCWSTR, PCWSTR, PCWSTR, PCWSTR);

#endif // LOGGER_H_INCLUDED