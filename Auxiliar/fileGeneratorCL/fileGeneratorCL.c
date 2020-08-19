#include "C:\Users\radut\Desktop\Aplicatii in C\Aplicatii\MAD OS Command Line\Command Line\mados.h"
#define lowLimit 32
#define highLimit 126

int main(){
    SetConsoleCtrlHandler(NULL,FALSE);
    wchar_t generateFileFullName[MAX_PATH];
    printf("File-Path:");
    fgetws(generateFileFullName,MAX_PATH,stdin);
    if(generateFileFullName[wcslen(generateFileFullName)-1] == '\n'){
        generateFileFullName[wcslen(generateFileFullName)-1] = '\0';

    }

    if(wStringCheck(generateFileFullName) == 1){
        return 1;

    }

    if(pathType(generateFileFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(generateFileFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    char content[BLOCK];
    content[BLOCK -1] = '\n';

    DWORD error = 0;
    HANDLE writeFileHandler = NULL;
    if((writeFileHandler = CreateFileW(generateFileFullName,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
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

        printf("CreateFileAWrite:%lu\n\n",error);
        ExitProcess(error);

    }

    unsigned long sizeInMB = 0;
    unsigned long remaining = 0;
    double status = 0;
    printf("Size(MB):");
    scanf("%lu",&sizeInMB);
    sizeInMB = sizeInMB * 1024*1024;
    remaining = sizeInMB;
    DWORD nrWritingBytes = BLOCK;
    DWORD nrWriteBytes = 0;
    while(remaining > 0){
        if(remaining <= BLOCK){
            nrWritingBytes = remaining;

        }

        for(int i = 0; i < (nrWritingBytes-1); i++){
            content[i] = (rand() % (highLimit - lowLimit)) +lowLimit;
        }
        content[BLOCK -1] = '\n';

        BOOL writeCheck;
        if((writeCheck = WriteFile(writeFileHandler,content,nrWritingBytes,&nrWriteBytes,NULL)) == FALSE){
                error = GetLastError();
                printf("WriteCheck:%lu\n",error);
                ExitProcess(error);
        }


        remaining = remaining - nrWriteBytes;
        status =((((double)sizeInMB) - (double)remaining)/(double)sizeInMB)*100;
        printf("\rGenerating...%.2f%% Complete!",status);

    }

    if(CloseHandle(writeFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    printf("\nFile was generating successfully!\n\n");

    return 0;
}
