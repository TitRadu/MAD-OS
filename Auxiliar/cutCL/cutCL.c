#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
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

int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    char source[PATH];
    char destination[PATH];
    printf("Source-File:");gets(source);
    if(stringCheck(source) == 1){
        ExitProcess(1);

    }

    DWORD error = 0;

    LPOFSTRUCT fileInformation = malloc(sizeof(OFSTRUCT));
    HANDLE readFileHandler = NULL;
    if((readFileHandler = CreateFileA(source,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == 2){
            printf("The system cannot find the file specified.\n");
            ExitProcess(2);

        }
        if(error == 3){
            printf("A part from source path isn't a directory!\n");
            ExitProcess(3);

        }
        if(error == 5){
            printf("Source is a directory or access is denied!\n");
            ExitProcess(5);
        }
        if(error == 123){
            printf("SourceFilePath is invalid!\n");
            ExitProcess(123);

        }
        printf("CreateFileARead:%d\n",error);
        ExitProcess(error);

    }

    struct _stat st;
    if(_stat(source,&st) < 0){
        if(errno == ENOENT){
            return 0;

        }

        perror("StatCheck");
        ExitProcess(-1);

    }
    unsigned long long size = st.st_size;
    unsigned long long remaining = size;
    double status = 0;

    printf("Destination-File:");gets(destination);
    if(stringCheck(destination) == 1){
        ExitProcess(1);

    }

    HANDLE writeFileHandler = NULL;
    if((writeFileHandler = CreateFileA(destination,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == 80){
            printf("(Destination)The file exists.\n");
            ExitProcess(80);

        }
        if(error == 3){
            printf("A part from destination path isn't a directory!\n");
            ExitProcess(3);

        }
        if(error == 5){
            printf("Destination is a directory or access is denied!\n");
            ExitProcess(5);
        }
        if(error == 123){
            printf("DestinationFilePath is invalid!\n");
            ExitProcess(123);

        }

        printf("CreateFileAWrite:%d\n",error);
        ExitProcess(error);

    }

    LPVOID buffer = malloc(BLOCK);
    PDWORD nrReadBytes = malloc(sizeof(DWORD));
    PDWORD nrWriteBytes = malloc(sizeof(DWORD));
    BOOL readCheck;
    BOOL writeCheck;
    while((readCheck = ReadFile(readFileHandler,buffer,BLOCK,nrReadBytes,NULL)) == TRUE){
        if((writeCheck = WriteFile(writeFileHandler,buffer,*nrReadBytes,nrWriteBytes,NULL)) ==FALSE){
            error = GetLastError();
            printf("WriteCheck:%d\n",error);
            ExitProcess(error);
        }


        if(*nrReadBytes == 0){
            break;

        }

        remaining = remaining - *nrWriteBytes;
        status =((((double)size) - (double)remaining)/(double)size)*100;
        printf("\rGenerating...%.2f%% Complete!",status);

    }

    if(readCheck == FALSE){
        error = GetLastError();
        printf("ReadCheck:%d\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(readFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(CloseHandle(writeFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    printf("\nThe file was copying successfully!\n");
    error = 0;
    if(DeleteFile(source) == FALSE){
        error = GetLastError();
        printf("DeleteFileCheck:%d\n",error);
        ExitProcess(-1);

    }
    printf("The source file was deleted successfully!\n\n");

    return 0;

}
