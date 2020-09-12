#ifndef MADOS_H_INCLUDED
#define MADOS_H_INCLUDED
#define THIRTY 30
#define OH 100
#define PATH 1024
#define BLOCK 4096
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <ctype.h>
#include <lm.h>
#include <psapi.h>
#include <intsafe.h>
#include <shlwapi.h>
#include <errno.h>

typedef struct command{
char* commandName;
struct command* nextCommand;

}command;

void pause();
int pathType(wchar_t*);
void wStringInQuatationMarks(wchar_t*);
HANDLE getProcessHeapChecker();
int heapFreeChecker(HANDLE,DWORD,LPVOID);
int wExist(wchar_t*,wchar_t*);
int wAllSpaces(wchar_t*);
int wStringCheck(wchar_t*);
void forkk(wchar_t*,wchar_t*);
void newPath(wchar_t*);
void changePath(wchar_t*);
void parse(wchar_t*,wchar_t);
void createDirectoryWraper(wchar_t*);
void createDirectory(wchar_t*);//
void removeDirectoryWraper(wchar_t*);
int removeDirectory(wchar_t*);//
void removeDirectoryRecursiveWraper(wchar_t*);
void removeDirectoryRecursive(wchar_t*);//
void createFileWraper(wchar_t*);
void createFile(wchar_t*);//
void removeFileWraper(wchar_t*);
void removeFile(wchar_t*);//
void renameFileWraper();
void renameFile(wchar_t*,wchar_t*);
void start1();//
void start2(wchar_t*);///
int wNumberOfAparition(wchar_t*,wchar_t);
int wLastAparition(wchar_t*,wchar_t);
void back(wchar_t*);//
void cline();//
void clearr();//
void newCline();//
void ipc();//
void ipca();//
void openPathWraper();
void openPath(wchar_t*);//
void sort();//
void help();//
void copyFile(wchar_t*,wchar_t*);
void myCopyFile(char*);//
void generateFile();//
void connectToURLWraper();
void connectToURL(wchar_t*);///
void displayTime();//
void copyDirectoryWraper(char*);
void copyDirectory(wchar_t*,wchar_t*);
void backupWraper(wchar_t*);
void backup(wchar_t*,wchar_t*);
void fileContentWraper();
void fileContent(wchar_t*);//
void calc();//
void netshProfiles();
void netshPasswordWraper();
void netshPassword(wchar_t*);
int characterCheck(char);
int spaceCountCheck(char*);
int allDigits(char*);
int operatorCheck(char);
void eval(int, int, int);
char* breakString(char*, char*);
char* compute(char*);
void editor();
void statusCheck(NET_API_STATUS,LPDWORD);
void getUserInfoWraper();
void getUserInfo(wchar_t*);
void listUsers();
void listUserLocalGroupsWraper();
void listUserLocalGroups(wchar_t*);
void addUserWraper();
void addUser(wchar_t*,wchar_t*);
void deleteUserWraper();
void deleteUser(wchar_t*);
void changeUserPasswordWraper();
void changeUserPassword(wchar_t*,wchar_t*,wchar_t*);
void getLocalGroupInfoWraper();
void getLocalGroupInfo(wchar_t*);
void listLocalGroups();
void listLocalGroupMembersWraper();
void listLocalGroupMembers(wchar_t*);
void EnumProcessesWraper(DWORD*,DWORD*);
void listProcessesWraper();
void listProcesses(wchar_t*,char*);
void killProcessWraper();
void killProcess(DWORD);
void changeColorWraper(wchar_t*);
void changeColor(wchar_t*,wchar_t*);
void changeConsoleFontSize(char*);
void logOff();
void lockStation();
void shutDown(wchar_t*);
command* addCommand(command*,char*);
void grep();
void mergeFiles();
void mergePartOfFiles();
void filesDiferences();
void init();
unsigned long long fibonacci(int);
void printFibonacci();

#endif // MADOS_H_INCLUDED
