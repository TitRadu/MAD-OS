#ifndef GENERALHELPER_H_INCLUDED
#define GENERALHELPER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>

void pause();
int pathType(wchar_t*);
HANDLE getProcessHeapChecker();
int heapFreeChecker(HANDLE,DWORD,LPVOID);
int allSpaces(char*);
int stringCheck(char*);

#endif // GENERALHELPER_H_INCLUDED