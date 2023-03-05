#ifndef CONFIGURATIONINFO_H_INCLUDED
#define CONFIGURATIONINFO_H_INCLUDED
#include <Windows.h>

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

#endif // CONFIGURATIONINFO_H_INCLUDED