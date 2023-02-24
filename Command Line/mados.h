#ifndef MADOS_H_INCLUDED
#define MADOS_H_INCLUDED
#define WCHAR_EMPTY_STRING L""
#define CHAR_EMPTY_STRING ""
#define THIRTY 30
#define OH 100
#define PATH 1024
#define BLOCK 4096
#define ABSOLUTE_PATH 0
#define RELATIVE_PATH 1
#define CMD_COMMAND_NOT_CONFIGURED "Error in CMD directly related commands configuration.\n\
Check if COMSPEC system environment variable contains CMD absolute path.\n\n"
#define _WIN32_WINNT _WIN32_WINNT_WIN10
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

typedef struct command{
char* commandName;
struct command* nextCommand;

}command;

typedef struct CONSOLE_DATA{
    HANDLE consoleHandle;
    COORD currentCursorPosition;
    CONSOLE_SCREEN_BUFFER_INFO screen;

}CONSOLE_DATA;

typedef struct CmdCommandsStruct{
    WCHAR path[256];
    BOOL state;
} CmdCommands;

typedef struct PathDirectoryStruct{
    WCHAR path[256];
    BOOL state;
} PathDirectory;

struct ConfigurationInfo{
    CmdCommands cmdCommands;
    PathDirectory pathDirectory;
} configurationInfo;

void pause();
size_t ucslen(const UCHAR*);
int ucscmp(const UCHAR*, const UCHAR*);
int pathType(wchar_t*);
void wStringInQuatationMarks(wchar_t*);
HANDLE getProcessHeapChecker();
int heapFreeChecker(HANDLE,DWORD,LPVOID);
int wExist(wchar_t*,wchar_t*);
int allSpaces(char*);
int wAllSpaces(wchar_t*);
int uAllSpaces(const UCHAR*);
int stringCheck(char*);
int wStringCheck(wchar_t*);
int uStringCheck(const UCHAR*);
wchar_t* wStringWithoutLast(wchar_t*, wchar_t);
wchar_t* wStringLastPart(wchar_t*, wchar_t);
UCHAR* fgetus(UCHAR*, int, FILE*);
void initializeCmdCommandsConfigurationInfo();
void initializeMadOsConfigurationInfo();
void forkk(wchar_t*,wchar_t*, HANDLE);
void changePath(wchar_t*);
HANDLE getFileHandleWrapper(PWCHAR);
HANDLE getFileHandle(PWCHAR fileAbsolutePath);
void parse(wchar_t*, PWCHAR, wchar_t*, HANDLE);
void closeHandle(HANDLE);
PWCHAR preparePathDependingOnType(PWCHAR, PWCHAR);
void chooseFileOperation(wchar_t*,char*);
void fileOperationWraper(wchar_t*,char*);
BOOL createDirectory(wchar_t*);
void createHiddenDirectory(wchar_t*);//
int removeDirectory(wchar_t*);//
void removeDirectoryRecursive(wchar_t*, PWCHAR);//
void createFile(wchar_t*, unsigned int);//
void removeFileWraper(wchar_t*);
DWORD removeFile(wchar_t*);//
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
void ipc(HANDLE);//
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
void find(wchar_t*);
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
PWLAN_AVAILABLE_NETWORK getNetworkProprierties(HANDLE, GUID*, UCHAR*, LPCWSTR);
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
void setPathDirectoryConfigurationState();
void createPathDirectory();
void initializePathDirectory();
void pathCommandSelector(PCHAR, PWCHAR);
void listPathDirectory();
void addFileInPathDirectory(PWCHAR);
void removeFileFromPathDirectory();
void removePathDirectory();
void runFileFromPathDirectory(BOOL);

#endif // MADOS_H_INCLUDED
