#ifndef COMPUTEROPERATIONS_H_INCLUDED
#define COMPUTEROPERATIONS_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include <psapi.h>
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"

typedef struct CONSOLE_DATA{
    HANDLE consoleHandle;
    COORD currentCursorPosition;
    CONSOLE_SCREEN_BUFFER_INFO screen;

}CONSOLE_DATA;

void logOff();
void lockStation();
void shutDown(wchar_t*);
void getPartitions();
void displayComputerName();
void setComputerNameWraper();
void setComputerName(wchar_t*);
void systemInformationPrint();
void systemInformation();
CONSOLE_DATA consoleDataPreparing();
void liveSystemInformation();
void printEnvironmentVariableValueWrapper();
void printEnvironmentVariableValue(PWCHAR);
void enumerateDeviceDrivers();

#endif // COMPUTEROPERATIONS_H_INCLUDED
