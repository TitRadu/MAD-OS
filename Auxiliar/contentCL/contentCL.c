#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define PATH 1024
#define BLOCK 4096

int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);

    DWORD error = 0;
    HANDLE readFileHandler = NULL;
    if((readFileHandler = CreateFileA(argv[1],GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
       error = GetLastError();
        if(error == 2){
            printf("The system cannot find the file specified.\n\n");
            ExitProcess(2);

        }
        if(error == 3){
            printf("A part from source path isn't a directory!\n\n");
            ExitProcess(3);

        }
        if(error == 5){
            printf("Source is a directory,not a regular file!\n\n");
            ExitProcess(5);
        }
        if(error == 123){
            printf("Source must be a relative path!\n\n");
            ExitProcess(123);

        }
        printf("CreateFileARead:%d\n",error);
        ExitProcess(error);

    }

    char* buffer = malloc(BLOCK);
    PDWORD nrReadBytes = malloc(sizeof(DWORD));
    BOOL readCheck;

    while((readCheck = ReadFile(readFileHandler,buffer,BLOCK,nrReadBytes,NULL)) == TRUE){
        for(int i = 0;i < *nrReadBytes;i++){
            printf("%c",buffer[i]);

        }

        if(*nrReadBytes == 0){
            break;

        }

    }

    if(readCheck == FALSE){
        error = GetLastError();
        printf("ReadCheck:%lu\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(readFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    free(buffer);
    free(nrReadBytes);

    printf("\nContent display finished!\n\n");

}


