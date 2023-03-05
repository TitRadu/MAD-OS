#include "CmdCommandsRunner.h"

void ipc(HANDLE outputFileHandler){
    forkk(configurationInfo.cmdCommands.path,L"/c ipconfig", outputFileHandler);

}

void ipca(){
    forkk(configurationInfo.cmdCommands.path,L"/c ipconfig /all", INVALID_HANDLE_VALUE);

}

void netshProfiles(){
    forkk(configurationInfo.cmdCommands.path,L"/c netsh wlan show profiles", INVALID_HANDLE_VALUE);

}

void netshPasswordWraper(){
    wchar_t ssid[OH];
    printf("SSID:");_getws(ssid);

    if(wStringCheck(ssid) == 1){
        return;

    }

    netshPassword(ssid);

}

void netshPassword(wchar_t* ssid){
    wchar_t command[OH];
    command[0] = '\0';
    wcscat_s(command,sizeof(command),L"/c netsh wlan show profile name=");
    wcscat_s(command,sizeof(command),ssid);
    wcscat_s(command,sizeof(command),L" ");
    wcscat_s(command,sizeof(command),L"key=clear");
    forkk(configurationInfo.cmdCommands.path, command, INVALID_HANDLE_VALUE);

}