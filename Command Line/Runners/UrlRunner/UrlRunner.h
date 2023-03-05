#ifndef URLRUNNER_H_INCLUDED
#define URLRUNNER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"

void connectToURLWraper();
void connectToURL(wchar_t*);
void imdbAdvancedSearchWrapper();
void youTubeSearchWrapper();

#endif // URLRUNNER_H_INCLUDED
