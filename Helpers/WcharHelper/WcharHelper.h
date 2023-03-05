#ifndef WCHARHELPER_H_INCLUDED
#define WCHARHELPER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\Macros.h"

void wStringInQuatationMarks(wchar_t*);
int wExist(wchar_t*,wchar_t*);
int wAllSpaces(wchar_t*);
int wStringCheck(wchar_t*);
wchar_t* wStringWithoutLast(wchar_t*, wchar_t);
wchar_t* wStringLastPart(wchar_t*, wchar_t);
int wNumberOfAparition(wchar_t*,wchar_t);
int wLastAparition(wchar_t*,wchar_t);

#endif // WCHARHELPER_H_INCLUDED
