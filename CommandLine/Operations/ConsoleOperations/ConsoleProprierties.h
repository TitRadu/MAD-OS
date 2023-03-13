#ifndef CONSOLEPROPRIERTIES_H_INCLUDED
#define CONSOLEPROPRIERTIES_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\..\GlobalVariables.h"
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"

typedef struct command{
char* commandName;
struct command* nextCommand;

}command;

void clearr();
void changeColorWraper(wchar_t*);
void changeColor(wchar_t*,wchar_t*);
void changeConsoleFontSize(char*);
command* addCommand(command*,char*);

#endif // CONSOLEPROPRIERTIES_H_INCLUDED
