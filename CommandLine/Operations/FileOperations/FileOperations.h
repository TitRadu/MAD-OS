#ifndef FILEOPERATIONS_H_INCLUDED
#define FILEOPERATIONS_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Navigator\Navigator.h"
#include "..\..\Runners\InternalRunner\InternalRunner.h"

void chooseFileOperation(wchar_t*,char*);
void fileOperationWraper(wchar_t*,char*);
BOOL createDirectory(wchar_t*);
void createHiddenDirectory(wchar_t*);//
int removeDirectory(wchar_t*);//
void removeDirectoryRecursive(wchar_t*, PWCHAR);//
void createFile(wchar_t*, unsigned int);//
DWORD removeFile(wchar_t*);//
void renameFileWraper(wchar_t*);
void renameFile(wchar_t*,wchar_t*);
BOOL changeFileAttributtes(PDWORD, char*);
void setFileProperties(wchar_t*, char*);
void copyFile(wchar_t*,wchar_t*);
void copyDirectoryWraper(wchar_t*,char*);
void copyDirectory(wchar_t*,wchar_t*);
HANDLE getFileHandleWrapper(PWCHAR);
HANDLE getFileHandle(PWCHAR fileAbsolutePath);
void closeHandle(HANDLE);

#endif // FILEOPERATIONS_H_INCLUDED
