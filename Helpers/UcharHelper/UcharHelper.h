#ifndef UCHARHELPER_H_INCLUDED
#define UCHARHELPER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>

size_t ucslen(const UCHAR*);
int ucscmp(const UCHAR*, const UCHAR*);
int uAllSpaces(const UCHAR*);
int uStringCheck(const UCHAR*);
UCHAR* fgetus(UCHAR*, int, FILE*);

#endif // UCHARHELPER_H_INCLUDED
