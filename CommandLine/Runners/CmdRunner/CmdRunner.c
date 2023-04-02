#include "CmdRunner.h"

void initializeCmdCommandsConfigurationInfo()
{
    LogA("mados", __FILE__, INFOA, __FUNCTION__);
    configurationInfo.cmdCommands.state = FALSE;
    DWORD error = 0;
    if(GetEnvironmentVariableW(L"COMSPEC", configurationInfo.cmdCommands.path, MAX_PATH) == 0){
        error = GetLastError();
        printf(CMD_COMMAND_NOT_CONFIGURED);
        printf("MainError:%lu\n", error);
        LogA("mados", __FILE__, WRNA, "CmdCommands configuration configuration failed!");
        return;
    }

    LogA("mados", __FILE__, INFOA, "CmdCommands configuration successfully!");
    configurationInfo.cmdCommands.state = TRUE;
}

void cmdRunnerWrapper(BOOL isLocalMode, BOOL isCommandRun){
    WCHAR command[1024] = WCHAR_EMPTY_STRING;
    
    if(isCommandRun){
        printf("Command:");
        fgetws(command,MAX_PATH,stdin);
    }

    cmdRunner(command, isLocalMode);

}

void cmdRunner(PWCHAR command, BOOL isLocalMode){
    if(isLocalMode){
        forkk(configurationInfo.cmdCommands.path, command, INVALID_HANDLE_VALUE);

    }
    else{
        HINSTANCE error = 0;
        if((error = ShellExecuteW(NULL,L"open",configurationInfo.cmdCommands.path,command,NULL,1)) <= (HINSTANCE)32){
        printf("CmdRunnerShellExecuteError:%p!\n", error);
        return;

        }

    }

}