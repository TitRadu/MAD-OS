#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>
#define lowLimit 32
#define highLimit 126
#define PATH 1024
#define BLOCK 4096

int allSpaces(char* string){
    for(int i = 0;i < strlen(string);i++){
        if(string[i] != 32){
            return 0;

        }
    }

    return 1;
}

int stringCheck(char *string){
    if(strcmp(string,"") == 0 || allSpaces(string) == 1){
        printf("Argument is empty or contains only spaces!\n");
        return 1;

    }

    return 0;

}

int main(){
    SetConsoleCtrlHandler(NULL,FALSE);
    char path[PATH];
    printf("File-Path:");
    gets(path);
    if(stringCheck(path) == 1){
        return 1;

    }

    char content[BLOCK];
    content[BLOCK -1] = '\n';

    DWORD error = 0;
    HANDLE writeFileHandler = NULL;
    if((writeFileHandler = CreateFileA(path,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == 80){
            printf("The file exists.\n\n");
            ExitProcess(80);

        }
        if(error == 3){
            printf("A part from destination path isn't a directory!\n\n");
            ExitProcess(3);

        }
        if(error == 5){
            printf("Destination path is a directory or access is denied!\n\n");
            ExitProcess(5);

        }

        printf("CreateFileAWrite:%d\n\n",error);
        ExitProcess(error);

    }

    unsigned long long size = 0;
    unsigned long long remaining = 0;
    double status = 0;
    printf("Size(MB):");
    scanf("%lld",&size);
    size = size * 1024*1024;
    remaining = size;
    DWORD nrWritingBytes = BLOCK;
    while(remaining > 0){
        if(remaining <= BLOCK){
            nrWritingBytes = remaining;

        }

        for(int i = 0; i < (nrWritingBytes-1); i++){
            content[i] = (rand() % (highLimit - lowLimit)) +lowLimit;
        }
        content[BLOCK -1] = '\n';
        PDWORD nrWriteBytes = malloc(sizeof(DWORD));
        BOOL writeCheck;
        if((writeCheck = WriteFile(writeFileHandler,content,nrWritingBytes,nrWriteBytes,NULL)) == FALSE){
                error = GetLastError();
                printf("WriteCheck:%d\n",error);
                ExitProcess(error);
        }


        remaining = remaining - *nrWriteBytes;
        status =((((double)size) - (double)remaining)/(double)size)*100;
        printf("\rGenerating...%.2f%% Complete!",status);

    }

    if(CloseHandle(writeFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    printf("\nFile was generating successfully!\n\n");

    return 0;
}
