#ifndef MADOS_H_INCLUDED
#define MADOS_H_INCLUDED
#define EMPTY_STRING L""
#define THIRTY 30
#define OH 100
#define PATH 1024
#define BLOCK 4096
#define ABSOLUTE_PATH 0
#define RELATIVE_PATH 1
#define CMD_COMMAND_NOT_CONFIGURED "Error in CMD directly related commands configuration.\n\
Check if COMSPEC system environment variable contains CMD absolute path.\n\n"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <ctype.h>
#include <lm.h>
#include <psapi.h>
#include <intsafe.h>
#include <shlwapi.h>
#include <wlanapi.h>
#include <bthsdpdef.h>
#include <bluetoothapis.h>
#include <bcrypt.h>
#include <errno.h>

WCHAR cmdPath[256];

typedef struct command{
char* commandName;
struct command* nextCommand;

}command;

typedef struct CONSOLE_DATA{
    HANDLE consoleHandle;
    COORD currentCursorPosition;
    CONSOLE_SCREEN_BUFFER_INFO screen;

}CONSOLE_DATA;

void pause();
int pathType(wchar_t*);
void wStringInQuatationMarks(wchar_t*);
HANDLE getProcessHeapChecker();
int heapFreeChecker(HANDLE,DWORD,LPVOID);
int wExist(wchar_t*,wchar_t*);
int wAllSpaces(wchar_t*);
int wStringCheck(wchar_t*);
wchar_t* wStringWithoutLast(wchar_t*,wchar_t);
wchar_t* wStringLastPart(wchar_t*,wchar_t);
void forkk(wchar_t*,wchar_t*);
void changePath(wchar_t*);
void parse(wchar_t*,wchar_t);
void chooseFileOperation(wchar_t*,char*);
void fileOperationWraper(wchar_t*,char*);
BOOL createDirectory(wchar_t*);
void createHiddenDirectory(wchar_t*);//
int removeDirectory(wchar_t*);//
void removeDirectoryRecursive(wchar_t*);//
void createFile(wchar_t*, unsigned int);//
void removeFileWraper(wchar_t*);
void removeFile(wchar_t*);//
void renameFileWraper(wchar_t*);
void renameFile(wchar_t*,wchar_t*);
BOOL changeFileAttributtes(PDWORD, char*);
void setFileProperties(wchar_t*, char*);
void openDefault();//
void openFileWithProgramWraper(wchar_t*);
void openFileWithProgram(wchar_t*,wchar_t*);///
void runWraper(wchar_t*, BOOL);
void run(wchar_t*, wchar_t*, BOOL);
int wNumberOfAparition(wchar_t*,wchar_t);
int wLastAparition(wchar_t*,wchar_t);
void back(wchar_t*);//
void cline(BOOL);//
void cmdRunnerWrapper(BOOL, BOOL);
void cmdRunner(PWCHAR, BOOL);
void clearr();//
void newCline();//
void ipc();//
void ipca();//
void openFileWraper(wchar_t*);
void openFile(wchar_t*,wchar_t*);//
void sortFilesWraper(wchar_t*);
void sortFiles(wchar_t*);
void sortDirectory();//
void help();//
void copyFile(wchar_t*,wchar_t*);
void myCopyFile(char*);//
void generateFile();//
void cryptFile();
void decryptFile();
void connectToURLWraper();
void connectToURL(wchar_t*);///
void displayTime();//
void timerUp();
void timerDown();
void activeTime();
void copyDirectoryWraper(wchar_t*,char*);
void copyDirectory(wchar_t*,wchar_t*);
void backupWraper(wchar_t*);
void backup(wchar_t*);
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
void getPartitions();
void setComputerNameWraper();
void setComputerName(wchar_t*);
void displayComputerName();
void systemInformationPrint();
void systemInformation();
CONSOLE_DATA consoleDataPreparing();
void liveSystemInformation();
void enumWlanInterfaces();
GUID* obtainGUIDFromStringWraper();
GUID* obtainGUIDFromString(wchar_t*);
void sendGUIDAsParameter(char*);
void enumAvaibleNetworks(GUID*);
void disconnectWlanInterface(GUID*);
PWLAN_AVAILABLE_NETWORK getNetworkProprierties(HANDLE, GUID*, char*, LPCWSTR);
void connectWlanInterfaceWraper();
void connectWlanInterface(GUID*, DOT11_SSID, LPCWSTR);
void enumerateBluetoothRadios();
void printBluetoothDeviceInformations(BLUETOOTH_DEVICE_INFO);
void enumerateBluetoothDevices();
void printEnvironmentVariableValueWrapper();
void printEnvironmentVariableValue(PWCHAR);
void enumerateDeviceDrivers();
void imdbAdvancedSearchWrapper();
void youTubeSearchWrapper();

#endif // MADOS_H_INCLUDED
