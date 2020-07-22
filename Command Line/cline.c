#include "mados.h"

int main(){
    SetConsoleCtrlHandler(NULL,TRUE);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAD OS Command Line Version 1.0~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(c) 2020 MAD OS Software. All rights reserved!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    DWORD userSize = THIRTY;
    char userName[THIRTY];
    if(!GetUserName(userName,&userSize)){
        printf("GetUserNameError");
        ExitProcess(-1);

    }

    DWORD PCsize = THIRTY;
    char PCname[THIRTY];
    if(!GetComputerName(PCname,&PCsize)){
        printf("GetUserNameError");
        ExitProcess(-1);

    }
    char* command = malloc(OH);
    wchar_t path[PATH];
    printf("Starting path:");
    _getws(path);

    int pathCheck = 0;
    if((pathCheck=wExist(path,L"")) == 0){
        printf("This path doesn't exist as file!\n");
        pause();
        ExitProcess(-1);

    }else{
        if(pathCheck != 2){
            printf("This path isn't a directory!\n");
            pause();
            ExitProcess(-1);

        }
    }

    if(wcslen(path) == 3){

    }else{
        wcscat(path,L"\\");

    }

    fflush(stdin);
    while(1){
        printf("%s@%s->",userName,PCname);
        wprintf(L"%s:",path);
        fflush(stdin);
        gets(command);
        if(strcmp(command,"exit") == 0){
            printf("Exit from command line!\n");
            pause();
            return 0;

        }

        if(strcmp(command,"") == 0){
            continue;

        }

        if(strcmp(command,"help") == 0){
            help();
            continue;

        }

        if(strcmp(command,"cline") == 0){
            cline();
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
            ipc();
            continue;
        }

        if(strcmp(command,"ipca") == 0){
            ipca();
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

        if(strcmp(command,"nwpath") == 0){
            newPath(path);
            continue;

        }

        if(strcmp(command,"chpath") == 0){
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
            createDirectoryWraper(path);
            continue;

        }

        if(strcmp(command,"rdir") == 0){
            removeDirectoryWraper(path);
            continue;

        }

        if(strcmp(command,"Rdir") == 0){
            removeDirectoryRecursiveWraper(path);
            continue;

        }

        if(strcmp(command,"ren") == 0){
            renameFileWraper();
            continue;

        }

        if(strcmp(command,"cfile") == 0){
            createFileWraper(path);
            continue;

        }

        if(strcmp(command,"rfile") == 0){
            removeFileWraper(path);
            continue;

        }

        if(strcmp(command,"start1") == 0){
            start1();
            continue;

        }

        if(strcmp(command,"start2") == 0){
            start2(path);
            continue;

        }

        if(strcmp(command,"opath") == 0){
            openPathWraper();
            continue;

        }

        if(strcmp(command,"sort") == 0){
            sort();
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

        if(strcmp(command,"url") == 0){
            connectToURLWraper();
            continue;

        }

        if(strcmp(command,"date") == 0){
            displayTime();
            continue;

        }

        if(strcmp(command,"copyD") == 0){
            copyDirectoryWraper("copy");
            continue;

        }

        if(strcmp(command,"cutD") == 0){
            copyDirectoryWraper("cut");
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
            netshProfiles();
            continue;

        }

        if(strcmp(command,"wifip") == 0){
            netshPasswordWraper();
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

        printf("Incorrect command!\n");

    }

    return 0;
}
