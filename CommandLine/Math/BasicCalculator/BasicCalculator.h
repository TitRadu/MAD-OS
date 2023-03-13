#ifndef BASICCALCULATOR_H_INCLUDED
#define BASICCALCULATOR_H_INCLUDED
#include <stdio.h>
#include <Windows.h>

int characterCheck(char);
int spaceCountCheck(char*);
int allDigits(char*);
int operatorCheck(char);
void eval(int, int, int);
char* breakString(char*, char*);
char* compute(char*);

#endif // BASICCALCULATOR_H_INCLUDED