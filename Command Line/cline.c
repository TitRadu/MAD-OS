#include "mados.h"

int main(){
    SetConsoleCtrlHandler(NULL,TRUE);
    extern HANDLE processHeap;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return 1;

    }
    extern unsigned long long values[];
    init(values);

    DWORD cmdCommandsAreNotCofigured = 0;
    if(GetEnvironmentVariableW(L"COMSPEC", cmdPath, MAX_PATH) == 0){
        cmdCommandsAreNotCofigured = GetLastError();
        printf(CMD_COMMAND_NOT_CONFIGURED);
        printf("MainError:%lu\n", cmdCommandsAreNotCofigured);
    }

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAD OS Command Line Version 1.0~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(c) 2020 MAD OS Software. All rights reserved!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    DWORD userSize = THIRTY;
    wchar_t userName[THIRTY];
    if(!GetUserNameW(userName,&userSize)){
        printf("GetUserNameError");
        ExitProcess(-1);

    }

    DWORD PCsize = THIRTY;
    wchar_t PCname[THIRTY];
    if(!GetComputerNameW(PCname,&PCsize)){
        printf("GetUserNameError");
        ExitProcess(-1);

    }
    int commandsCount = 0;
    command* history = NULL;
    command* aux;
    char command[MAX_PATH];
    wchar_t path[MAX_PATH];

    GetEnvironmentVariableW(L"USERPROFILE", path, MAX_PATH);
    wcscat_s(path,sizeof(path),L"\\");

    while(1){
        wprintf(L"%s@%s->%s:",userName,PCname,path);
        fflush(stdin);

        fgets(command,MAX_PATH,stdin);
        if(command[strlen(command)-1] == '\n'){
            command[strlen(command)-1] = '\0';
        }


        if(strcmp(command,"exit") == 0){
            printf("Exit from command line!\n");
            pause();
            return 0;

        }

        if(strcmp(command,"") == 0){
            continue;

        }

        history = addCommand(history,command);

        if(strcmp(command,"help") == 0){
            help();
            continue;

        }

        if(strcmp(command,"cline") == 0){
            cline(FALSE);
            continue;

        }

        if(strcmp(command,"lcline") == 0){
            cline(TRUE);
            continue;

        }

        if(strcmp(command,"cmd") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                cmdRunnerWrapper(FALSE, FALSE);
            }
            continue;
        }

        if(strcmp(command,"lcmd") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                cmdRunnerWrapper(TRUE, FALSE);
            }
            continue;
        }

        if(strcmp(command,"runcmd") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                cmdRunnerWrapper(FALSE, TRUE);
            }
            continue;
        }

        if(strcmp(command,"lruncmd") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                cmdRunnerWrapper(TRUE, TRUE);
            }
            continue;
        }

        if(strcmp(command,"clear") == 0){
            clearr();
            continue;

        }

        if(strcmp(command,"nwcline") == 0){
            newCline();

        }

        if(strcmp(command,"ipc") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                ipc();
            }
            continue;
        }

        if(strcmp(command,"ipca") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                ipca();
            }
            continue;
        }

        if(strcmp(command,"cpath") == 0){
            wprintf(L"%s\n",path);
            continue;

        }

        if(strcmp(command,"-path") == 0){
            back(path);
            continue;

        }

        if(strcmp(command,"cp") == 0){
            changePath(path);
            continue;

        }

        if(strcmp(command,"list") == 0){
            printf("\n");
            parse(path,'-');
            printf("\n");
            continue;

        }

        if(strcmp(command,"Rlist") == 0){
            printf("\n");
            parse(path,'r');
            printf("\n");
            continue;

        }

        if(strcmp(command,"cdir") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"chdir") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"rdir") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"Rdir") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"ren") == 0){
            renameFileWraper(path);
            continue;

        }

        if(strcmp(command,"cfile") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"chfile") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"rfile") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"hide") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"show") == 0){
            fileOperationWraper(path,command);
            continue;

        }

        if(strcmp(command,"open") == 0){
            openDefault();
            continue;

        }

        if(strcmp(command,"openF") == 0){
            openFileWraper(path);
            continue;

        }

        if(strcmp(command,"openFP") == 0){
            openFileWithProgramWraper(path);
            continue;

        }

        if(strcmp(command,"run") == 0){
            runWraper(path, TRUE);
            continue;

        }

        if(strcmp(command,"runP") == 0){
            runWraper(path, FALSE);
            continue;

        }

        if(strcmp(command,"sortF") == 0){
            sortFilesWraper(path);
            continue;

        }

        if(strcmp(command,"sortD") == 0){
            sortDirectory();
            continue;

        }

        if(strcmp(command,"copyF") == 0){
            myCopyFile("copy");
            continue;

        }

        if(strcmp(command,"cutF") == 0){
            myCopyFile("cut");
            continue;

        }

        if(strcmp(command,"genf") == 0){
            generateFile();
            continue;

        }

        if(strcmp(command,"crypt") == 0){
            cryptFile();
            continue;

        }

        if(strcmp(command,"decrypt") == 0){
            decryptFile();
            continue;

        }

        if(strcmp(command,"url") == 0){
            connectToURLWraper();
            continue;

        }

        if(strcmp(command,"date") == 0){
            displayTime();
            continue;

        }

        if(strcmp(command,"utimer") == 0){
            timerUp();
            continue;

        }

        if(strcmp(command,"dtimer") == 0){
            timerDown();
            continue;

        }

        if(strcmp(command,"active") == 0){
            activeTime();
            continue;

        }

        if(strcmp(command,"copyD") == 0){
            copyDirectoryWraper(path,"copy");
            continue;

        }

        if(strcmp(command,"cutD") == 0){
            copyDirectoryWraper(path,"cut");
            continue;

        }

        if(strcmp(command,"bckp") == 0){
            backupWraper(path);
            continue;

        }

        if(strcmp(command,"cat") == 0){
            fileContentWraper();
            continue;

        }

        if(strcmp(command,"calc") == 0){
            calc();
            continue;

        }

        if(strcmp(command,"wifi") == 0){
            if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                netshProfiles();
            }
            continue;
        }

        if(strcmp(command,"wifip") == 0){
           if(cmdCommandsAreNotCofigured){
                printf(CMD_COMMAND_NOT_CONFIGURED);
            }
            else{
                netshPasswordWraper();
            }
            continue;
        }

        if(strcmp(compute(command),"Match") == 0){
            continue;

        }

        if(strcmp(command,"editor") == 0){
            editor();
            continue;

        }

        if(strcmp(command,"user") == 0){
            getUserInfoWraper();
            continue;

        }

        if(strcmp(command,"users") == 0){
            printf("\n");
            listUsers();
            continue;

        }

        if(strcmp(command,"auser") == 0){
            addUserWraper();
            continue;

        }

        if(strcmp(command,"duser") == 0){
            deleteUserWraper();
            continue;

        }

        if(strcmp(command,"cpass") == 0){
            changeUserPasswordWraper();
            continue;

        }

        if(strcmp(command,"group") == 0){
            getLocalGroupInfoWraper();
            continue;

        }

        if(strcmp(command,"groups") == 0){
            printf("\n");
            listLocalGroups();
            continue;

        }

        if(strcmp(command,"members") == 0){
            listLocalGroupMembersWraper();
            continue;

        }

        if(strcmp(command,"userg") == 0){
            listUserLocalGroupsWraper();
            continue;

        }

        if(strcmp(command,"ps") == 0){
            listProcesses(NULL,NULL);
            continue;

        }

        if(strcmp(command,"psName") == 0){
            listProcessesWraper(NULL);
            continue;

        }

        if(strcmp(command,"term") == 0){
            killProcessWraper();
            continue;

        }

        if(strcmp(command,"termn") == 0){
            listProcessesWraper("r");
            continue;

        }

        if(strcmp(command,"tcolor") == 0){
            changeColorWraper(L"text");
            continue;

        }

        if(strcmp(command,"bcolor") == 0){
            changeColorWraper(L"background");
            continue;

        }

        if(strcmp(command,"f+") == 0){
            changeConsoleFontSize("up");
            continue;

        }

        if(strcmp(command,"f-") == 0){
            changeConsoleFontSize("down");
            continue;

        }

        if(strcmp(command,"logoff") == 0){
            logOff();
            continue;

        }

        if(strcmp(command,"lock") == 0){
            lockStation();
            continue;

        }

        if(strcmp(command,"restart") == 0){
            shutDown(L"restart");
            continue;

        }

        if(strcmp(command,"sd") == 0){
            shutDown(L"");
            continue;

        }

        if(strcmp(command,"history") == 0){
            commandsCount = 0;
            for(aux = history; aux != NULL; aux=aux->nextCommand){
                commandsCount++;
                printf("%d. %s\n",commandsCount,aux->commandName);

            }
            printf("\n");
            continue;

        }

        if(strcmp(command,"grep") == 0){
            grep();
            continue;

        }

        if(strcmp(command,"merge") == 0){
            mergeFiles();
            continue;

        }

        if(strcmp(command,"mergeP") == 0){
            mergePartOfFiles();
            continue;

        }

        if(strcmp(command,"diff") == 0){
            filesDiferences();
            continue;

        }

        if(strcmp(command,"fib") == 0){
            printFibonacci();
            continue;

        }

        if(strcmp(command,"partitions") == 0){
            getPartitions();
            continue;

        }

        if(strcmp(command,"pcname") == 0){
            displayComputerName();
            continue;

        }


        if(strcmp(command,"cpcname") == 0){
            setComputerNameWraper();
            continue;

        }

        if(strcmp(command,"sinfo") == 0){
            systemInformation();
            continue;

        }

        if(strcmp(command,"liveinfo") == 0){
            liveSystemInformation();
            continue;

        }

        if(strcmp(command,"iwlan") == 0){
            enumWlanInterfaces();
            continue;

        }

        if(strcmp(command,"nwlan") == 0){
            sendGUIDAsParameter("networks");
            continue;

        }

        if(strcmp(command,"disconnect") == 0){
            sendGUIDAsParameter("disconnect");
            continue;

        }

        if(strcmp(command,"connect") == 0){
            connectWlanInterfaceWraper();
            continue;

        }

        if(strcmp(command,"bthrad") == 0){
            enumerateBluetoothRadios();
            continue;

        }

        if(strcmp(command,"bthdev") == 0){
            enumerateBluetoothDevices();
            continue;

        }

        if(strcmp(command,"env") == 0){
            printEnvironmentVariableValueWrapper();
            continue;

        }

        if(strcmp(command,"drivers") == 0){
            enumerateDeviceDrivers();
            continue;

        }

        if(strcmp(command,"film") == 0){
            imdbAdvancedSearchWrapper();
            continue;

        }

        if(strcmp(command,"youtube") == 0){
            youTubeSearchWrapper();
            continue;

        }
        printf("Incorrect command!\n");

    }

    return 0;
}
