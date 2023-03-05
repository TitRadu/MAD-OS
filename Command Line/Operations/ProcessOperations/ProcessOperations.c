#include "ProcessOperations.h"

void forkk(wchar_t *application,wchar_t *args, HANDLE outputFileHandler){
    STARTUPINFOW s;
    PROCESS_INFORMATION p;
    ZeroMemory(&s,sizeof(STARTUPINFOW));
    s.cb = sizeof(STARTUPINFOW);
    BOOL bInheritHandles = FALSE;
    if(outputFileHandler != INVALID_HANDLE_VALUE){
        bInheritHandles = TRUE;
        s.hStdOutput = outputFileHandler;
        s.dwFlags |= STARTF_USESTDHANDLES;
    }
    ZeroMemory(&p,sizeof(PROCESS_INFORMATION));

    wchar_t commandLine[MAX_PATH*2];
    wcscpy_s(commandLine,sizeof(commandLine),L"\"");
    wcscat_s(commandLine,sizeof(commandLine),application);
    wcscat_s(commandLine,sizeof(commandLine),L"\"");
    wcscat_s(commandLine,sizeof(commandLine),L" ");
    wcscat_s(commandLine,sizeof(commandLine),args);

    wchar_t applicationCopy[MAX_PATH];
    wcscpy_s(applicationCopy,sizeof(applicationCopy),application);
    wchar_t* applicationDirectory = wStringWithoutLast(applicationCopy,'\\');

    BOOL createProccesCheck = FALSE;
    SetConsoleCtrlHandler(NULL,FALSE);
createProccesCheck = CreateProcessW(
application,
commandLine,
NULL,
NULL,
bInheritHandles,
0,
NULL,
applicationDirectory,
&s,
&p
    );
    SetConsoleCtrlHandler(NULL,TRUE);
    DWORD error = 0;
    if(createProccesCheck == FALSE){
        error = GetLastError();
        if(error == ERROR_BAD_EXE_FORMAT){
            printf("First argument is a non-executable file!\n\n");
            return;

        }        

        if(error == 740){
            printf("You don't have permission to do this operation.Please run command line as administrator!\n\n");
            return;

        }

        printf("ForkkCreateProcessError:%lu\n",error);
        ExitProcess(error);

    }

    if ((wcscmp(application,L"VBCalculator.exe") != 0) && (wcscmp(application,L"TextEditor.exe") != 0))
    if(WaitForSingleObject(p.hProcess,INFINITE) == WAIT_FAILED){
        error = GetLastError();
        printf("ForkkWaitForSingleObjectError:%lu\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(p.hProcess) == FALSE){
        error = GetLastError();
        printf("ForkkCloseHandleHProcessError:%lu\n",error);
        return;

    }

    if(CloseHandle(p.hThread) == FALSE){
        error = GetLastError();
        printf("ForkkCloseHandleHThreadError:%lu\n",error);
        return;

    }

}

void EnumProcessesWraper(DWORD* processesList,DWORD* numberOfProcesses){
    DWORD returnBytes = 0;

    DWORD error = 0;
    if(EnumProcesses(processesList,2048,&returnBytes) == FALSE){
        error = GetLastError();
        printf("EnumProcessesError:%lu\n\n",error);
        ExitProcess(error);

    }
    (*numberOfProcesses) = returnBytes/sizeof(DWORD);

}

void listProcessesWraper(char* control){
    wchar_t processName[50];
    printf("Process name:");
    fgetws(processName,50,stdin);
    if(processName[wcslen(processName)-1] == '\n')
        processName[wcslen(processName)-1] = '\0';

    listProcesses(processName,control);

}

void listProcesses(wchar_t* pName,char* control){
    if(pName != NULL){
        if(wStringCheck(pName) == 1){
            return;

        }
    }

    printf("\nName\t\tPID\n");

    DWORD processesList[2048];
    DWORD numberOfProcesses = 0;
    int processCount = 0;
    DWORD error = 0;

    EnumProcessesWraper(processesList,&numberOfProcesses);


    wchar_t processName[OH] = L"Unkown";
    for(int i=0;i < numberOfProcesses;i++){
        if(processesList[i] == 0)
            continue;

        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,processesList[i]);
        if(processHandle == NULL){
            error = GetLastError();
            if(error == ERROR_ACCESS_DENIED){
                continue;

            }

            printf("ListProcessesOpenProcessError:%lu---PID:%lu\n",error,processesList[i]);
            continue;

        }

        if(processHandle != NULL){
            HMODULE firstModule;
            DWORD totalBytesNeededToStoreAllModules;
            if(EnumProcessModules(processHandle,&firstModule,sizeof(HMODULE),&totalBytesNeededToStoreAllModules) != FALSE ){
                if(GetModuleBaseNameW(processHandle,firstModule,processName,sizeof(processName)) == 0){
                   error = GetLastError();
                    printf("ListProcessesGetModuleBaseNameError:%lu---PID:%lu\n\n\n",error,processesList[i]);
                    continue;
                }

                if(pName != NULL){
                    if(wcscmp(pName,processName) == 0){
                       processCount++;
                       if(control == NULL){
                        wprintf(L"%s\t%lu\n",processName,processesList[i]);
                       }

                        if(control != NULL){
                            if(strcmp(control,"r") == 0){
                                if(wcscmp(pName,L"chrome.exe") == 0 && processCount > 1)
                                break;

                            wprintf(L"%s\t%lu--->Kill...\n",processName,processesList[i]);
                            killProcess(processesList[i]);

                            }

                        }

                    }

                }

            }else{
                    error = GetLastError();
                    printf("ListProcessesEnumProccesModules:%lu---PID:%lu\n\n\n",error,processesList[i]);
                    continue;
            }
        }
        if(pName == NULL){
            wprintf(L"%s\t%lu\n",processName,processesList[i]);
        }

            CloseHandle(processHandle);

    }

    if(pName != NULL){
        printf("\nProgram founds %d process with given name!\n\n",processCount);
    }

    printf("\n");
}

void killProcessWraper(){
    unsigned int killPid = -1;
    printf("PID:");scanf("%d",&killPid);
    killProcess(killPid);

}

void killProcess(DWORD killPid){
    if(killPid == GetCurrentProcessId()){
        printf("The specified PID is PID of current process!\n\n");
        return;
    }

    DWORD error = 0;
    HANDLE processHandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE,FALSE,killPid);
        if(processHandle == NULL){
            error = GetLastError();
            if(error == ERROR_ACCESS_DENIED){
                printf("Acces denied!\n\n");
                return;

            }

            if(error == ERROR_INVALID_PARAMETER){
                printf("There is not a process with this PID!\n\n");
                return ;

            }

            printf("KillProcessOpenProccesError:%lu---PID:%lu\n",error,killPid);
            return;

        }

    if(TerminateProcess(processHandle,-5) == 0){
        printf("TerminateProccesError:%lu---PID:%lu\n",error,killPid);
        return;

    }

    if(WaitForSingleObject(processHandle,INFINITE) == WAIT_FAILED){
        error = GetLastError();
        printf("WaitForSingleObjectCheck:%lu\n",error);
        return;

    }

    if(CloseHandle(processHandle) == FALSE){
        error = GetLastError();
        return;

    }

    printf("Process was killed succesfully!\n\n");
}