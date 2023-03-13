#ifndef CMDCOMMANDSRUNNER_H_INCLUDED
#define CMDCOMMANDSRUNNER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\ConfigurationInfo.h"
#include "..\..\Operations\ProcessOperations\ProcessOperations.h"

void ipc(HANDLE);
void ipca();
void netshProfiles();
void netshPasswordWraper();
void netshPassword(wchar_t*);

#endif // CMDCOMMANDSRUNNER_H_INCLUDED