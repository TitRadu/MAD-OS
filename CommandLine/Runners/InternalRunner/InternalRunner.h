#ifndef INTERNALRUNNER_H_INCLUDED
#define INTERNALRUNNER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\..\Logger\Logger.h"
#include "..\..\Operations\ProcessOperations\ProcessOperations.h"
#include "..\..\Navigator\Navigator.h"

void cline(BOOL);
void newCline();
void sortFilesWraper(wchar_t*);
void sortFiles(wchar_t*);
void sortDirectory();//
void myCopyFile(char*);//
void generateFile();//
void cryptFile();
void decryptFile();
void fileContentWraper();
void fileContent(wchar_t*);//
void calc();//
void editor();
void grep();
void mergeFiles();
void mergePartOfFiles();
void filesDiferences();
void find(wchar_t*);
void help();
void parse(wchar_t*, PWCHAR, wchar_t*, HANDLE);

#endif // INTERNALRUNNER_H_INCLUDED
