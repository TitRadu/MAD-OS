#ifndef PROCESSOPERATIONS_H_INCLUDED
#define PROCESSOPERATIONS_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include <psapi.h>
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"

void forkk(wchar_t*,wchar_t*, HANDLE);
void EnumProcessesWraper(DWORD*,DWORD*);
void listProcessesWraper();
void listProcesses(wchar_t*,char*);
void killProcessWraper();
void killProcess(DWORD);

#endif // PROCESSOPERATIONS_H_INCLUDED
