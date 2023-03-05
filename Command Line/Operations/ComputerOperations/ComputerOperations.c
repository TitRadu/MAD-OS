#include "ComputerOperations.h"

void logOff(){
    DWORD error = 0;
    if(ExitWindowsEx(EWX_LOGOFF,0) == FALSE){
        printf("LogOffError:%lu\n\n",error);
        return;

    }

}

void lockStation(){
    DWORD error = 0;
    if(LockWorkStation() == FALSE){
        printf("LockStationError:%lu\n\n",error);
        return;

    }

}

void shutDown(wchar_t* mode){
    unsigned int operation = 0;
    HANDLE tokenHandle;
    TOKEN_PRIVILEGES tokenPriv;

    DWORD error = 0 ;
    if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&tokenHandle) == 0){
        error = GetLastError();
        printf("ShutDownOpenProcessTokenError:%lu\n",error);
        return;

    }

    if(LookupPrivilegeValueW(NULL,L"SeShutdownPrivilege",&tokenPriv.Privileges[0].Luid) == 0){
        error = GetLastError();
        printf("ShutDownLookupPrivilegeValueError:%lu\n",error);
        return;

    }

    tokenPriv.PrivilegeCount = 1;
    tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if(AdjustTokenPrivileges(tokenHandle,FALSE,&tokenPriv,0,NULL,NULL) == 0){
        error = GetLastError();
        printf("ShutDownAdjustTokenPrivilegesError:%lu\n",error);
        return;

    }

    if(wcscmp(mode,L"restart") == 0){
        operation = EWX_REBOOT;

    }else{
        operation = EWX_POWEROFF;
    }

    if(ExitWindowsEx(operation | EWX_FORCE,SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_FLAG_PLANNED) == 0){
        error = GetLastError();
        printf("ShutDownExitWindowsExError:%lu\n",error);
        return;

    }

}

void getPartitions(){

    DWORD partitionNumber = 0;
    DWORD partitions = 0;

    if((partitions = GetLogicalDrives()) == FALSE){
        partitions = GetLastError();
        printf("GetPartitionsGetLogicalDrivesError:%lu\n\n",partitions);
        return;

    }

    printf("List of partitions:\n");
    for(int i = 0;i <= 26;i++){
        if(partitions & (1<<i)){
            partitionNumber++;
            printf("%c:\\\n",i+65);

        }

    }

    printf("\n");

}

void displayComputerName(){
    DWORD PCsize = THIRTY;
    wchar_t PCname[THIRTY];
    DWORD error = 0;

    if(!GetComputerNameExW(ComputerNamePhysicalDnsHostname, PCname,&PCsize)){
        error = GetLastError();
        printf("DisplayComputerNameGetComputerNameError:%lu\n",error);
        ExitProcess(-1);

    }

    wprintf(L"%ls\n",PCname);

}

void setComputerNameWraper(){
    wchar_t newComputerName[THIRTY];
    fgetws(newComputerName,THIRTY,stdin);
    if(newComputerName[wcslen(newComputerName)-1] == '\n'){
        newComputerName[wcslen(newComputerName)-1] = '\0';

    }

    if(wStringCheck(newComputerName) == 1){
        return;

    }

    setComputerName(newComputerName);

}
void setComputerName(wchar_t* newComputerName){
    DWORD error = 0;

    if(!SetComputerNameExW(ComputerNamePhysicalDnsHostname, newComputerName)){
        error = GetLastError();
        printf("SetComputerNameSetComputerNameError:%lu\n",error);
        ExitProcess(-1);

    }

    printf("To see changes you need to restart the computer!\n\n");

}

void systemInformationPrint(MEMORYSTATUSEX memoryStatus, PERFORMANCE_INFORMATION performanceInformation){
    double memoryLoadPercentage = 100 - ((double)memoryStatus.ullAvailPhys / memoryStatus.ullTotalPhys)* 100 ;
    double totalPhysicalGB = (double)memoryStatus.ullTotalPhys / 1073741824;
    double avaiblePhysicalGB = (double)memoryStatus.ullAvailPhys / 1073741824;
    double totalVirtualGB = (double)memoryStatus.ullTotalVirtual / 1073741824;
    double avaibleVirtualGB = (double)memoryStatus.ullAvailVirtual / 1073741824;


    printf("MemoryLoad: %lu%%\n", memoryStatus.dwMemoryLoad);
    printf("MemoryLoad: %.2f%%\n", memoryLoadPercentage);
    printf("TotalPhys: %.2f GB\n", totalPhysicalGB);
    printf("AvailablePhys: %.2f GB\n", avaiblePhysicalGB);
    printf("TotalVirtual: %.2f GB\n", totalVirtualGB);
    printf("AvailableVirtual: %.2f GB\n", avaibleVirtualGB);
    printf("Number of processess: %lu\n", performanceInformation.ProcessCount);
    printf("Number of threads: %lu\n", performanceInformation.ThreadCount);

}

void systemInformation(){
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    DWORD error = 0;

    if (GlobalMemoryStatusEx(&memoryStatus) == 0){
        error = GetLastError();
        printf("SystemInformationGlobalMemoryStatusExError:%lu\n", error);
        ExitProcess(error);

    }

    PERFORMANCE_INFORMATION performanceInformation;
    if (GetPerformanceInfo(&performanceInformation,sizeof(PERFORMACE_INFORMATION)) == 0){
        error = GetLastError();
        printf("SystemInformationGetPerformanceInfoError:%lu\n", error);
        ExitProcess(error);

    }

    systemInformationPrint(memoryStatus, performanceInformation);

}

CONSOLE_DATA consoleDataPreparing(){
    HANDLE console;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD error;

    if((console = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("ClearrGetStdHandleError:%lu\n",error);
        ExitProcess(error);

    }

    if(GetConsoleScreenBufferInfo(console,&screen) == 0){
        error = GetLastError();
        printf("ClearrGetConsoleScreenBufferError:%lu\n",error);
        ExitProcess(error);

    }

    CONSOLE_DATA consoleData;
    consoleData.consoleHandle = console;
    consoleData.currentCursorPosition =screen.dwCursorPosition;
    consoleData.screen = screen;

    return consoleData;

}

void liveSystemInformation(){
    PERFORMACE_INFORMATION performanceInformation;
    CONSOLE_DATA consoleData = consoleDataPreparing();
    DWORD error;

    CONSOLE_CURSOR_INFO consoleCursorInfo;
    if(GetConsoleCursorInfo(consoleData.consoleHandle, &consoleCursorInfo) == 0){
        error = GetLastError();
        printf("LiveSystemInformationGetConsoleCursorInfoError:%lu\n", error);
        ExitProcess(error);

    }

    consoleCursorInfo.bVisible = FALSE;

    if(SetConsoleCursorInfo(consoleData.consoleHandle, &consoleCursorInfo) == 0){
        error = GetLastError();
        printf("LiveSystemInformationSetConsoleCursorInfoError:%lu\n", error);
        ExitProcess(error);

    }

    while(1){
       if (GetPerformanceInfo(&performanceInformation,sizeof(PERFORMACE_INFORMATION)) == 0){
            error = GetLastError();
            printf("LiveSystemInformationGetPerformanceInfoError:%lu\n", error);
            ExitProcess(error);

        }


        ULONGLONG avaiblePhysicalBytes = performanceInformation.PhysicalAvailable * performanceInformation.PageSize;
        double memoryLoadPercentage = 100 - ((double) avaiblePhysicalBytes / (performanceInformation.PhysicalTotal * performanceInformation.PageSize))* 100 ;
        double avaiblePhysicalGB = (double)avaiblePhysicalBytes / 1073741824;

        printf("MemoryLoad: %.2f%%\n", memoryLoadPercentage);
        printf("AvailablePhys: %.2f GB\n", avaiblePhysicalGB);
        printf("Number of processess: %lu \n", performanceInformation.ProcessCount);
        printf("Number of threads: %lu \n", performanceInformation.ThreadCount);

        if(SetConsoleCursorPosition(consoleData.consoleHandle,consoleData.currentCursorPosition) == 0){
            error = GetLastError();
            printf("ClearrSetConsoleCursorPositionError:%lu\n",error);
            ExitProcess(error);

        }

        if(GetKeyState('S') & 0x8000){
            consoleCursorInfo.bVisible = TRUE;
            if(SetConsoleCursorInfo(consoleData.consoleHandle, &consoleCursorInfo) == 0){
                error = GetLastError();
                printf("LiveSystemInformationGlobalMemoryStatusExError:%lu\n", error);
                ExitProcess(error);

            }

            consoleData.currentCursorPosition.Y = consoleData.currentCursorPosition.Y + 5;
            if(SetConsoleCursorPosition(consoleData.consoleHandle,consoleData.currentCursorPosition) == 0){
                error = GetLastError();
                printf("ClearrSetConsoleCursorPositionError:%lu\n",error);
                ExitProcess(error);

            }

            printf("\n");
            break;

        }

    }

}

void printEnvironmentVariableValueWrapper()
{
    WCHAR environmentVariable[1024];
    
    printf("Variable:");
    fgetws(environmentVariable, 1024, stdin);
    if(environmentVariable[wcslen(environmentVariable)-1] == '\n'){
        environmentVariable[wcslen(environmentVariable)-1] = '\0';

    }

    printEnvironmentVariableValue(environmentVariable);
}

void printEnvironmentVariableValue(PWCHAR environmentVariable){
    if(wStringCheck(environmentVariable) == 1){
        return;

    }

    WCHAR environmentVariableValue[1024];
    DWORD error = 0;
    if(GetEnvironmentVariableW(environmentVariable, environmentVariableValue, 1024) == 0){
        error = GetLastError();
        if(error == ERROR_ENVVAR_NOT_FOUND){
            printf("The system could not find the environment option that was entered.\n\n");
            return;
        }
        printf("PrintEnvironmentVariableValueError:%lu\n", error);
        ExitProcess(error);
    }

    wprintf(L"%s\n\n", environmentVariableValue);
}

void enumerateDeviceDrivers(){
    LPVOID drivers[1024];
    DWORD numberOfBytesNeeded;
    int numberOfDrivers, i;
    DWORD error = 0;

    if(EnumDeviceDrivers(drivers, sizeof(drivers), &numberOfBytesNeeded) == TRUE){
        numberOfDrivers =  numberOfBytesNeeded / sizeof(drivers[0]);

        printf("Drivers are:(base name -> file name)\n");

        WCHAR driverName[1024];
        for(i=0; i<numberOfDrivers; i++){
            if(GetDeviceDriverBaseNameW(drivers[i], driverName, sizeof(driverName)) == TRUE){
                wprintf(L"Application need some changes. Contact the development engineer!\n");
                ExitProcess(-1);

            }else{
                error = GetLastError();
                if(error == ERROR_ENVVAR_NOT_FOUND){
                    wprintf(L"%d:%s", i+1, driverName);
                    if(GetDeviceDriverFileNameW(drivers[i], driverName, sizeof(driverName)) == TRUE){
                        wprintf(L"Application need some changes. Contact the development engineer!\n");
                        ExitProcess(-1);

                    }else{
                        error = GetLastError();
                        if(error == ERROR_ENVVAR_NOT_FOUND){
                            wprintf(L" \t-> \t%s\n",driverName);
                            continue;

                        }
                        printf("EnumerateDeviceDriversGetDeviceDriverFileNameWError:%lu\nl", error);
                        ExitProcess(error);

                    }

                }
                printf("EnumerateDeviceDriversGetDeviceDriverBaseNameWError:%lu\nl", error);
                ExitProcess(error);
            }

        }

    }else{
        error = GetLastError();
        printf("EnumerateDeviceDriversEnumDeviceDriversError:%lu", error);
        ExitProcess(error);
    }
    printf("\n");

}