#ifndef GENERALRUNNER_H_INCLUDED
#define GENERALRUNNER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Navigator\Navigator.h"
#include "..\..\Operations\ProcessOperations\ProcessOperations.h"

void openDefault();//
void openFileWraper(wchar_t*);
void openFile(wchar_t*,wchar_t*);//
void openFileWithProgramWraper(wchar_t*);
void openFileWithProgram(wchar_t*,wchar_t*);///
void runWraper(wchar_t*, BOOL);
void run(wchar_t*, wchar_t*, BOOL);

#endif // GENERALRUNNER_H_INCLUDED
