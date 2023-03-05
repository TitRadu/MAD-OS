#ifndef NAVIGATOR_H_INCLUDED
#define NAVIGATOR_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\GlobalVariables.h"
#include "..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"

void changePath(wchar_t*);
void back(wchar_t*);
PWCHAR preparePathDependingOnType(PWCHAR, PWCHAR);

#endif // NAVIGATOR_H_INCLUDED
