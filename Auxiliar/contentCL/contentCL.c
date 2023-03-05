#include <stdio.h>
#include <Windows.h>
#include "..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"

int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    LPWSTR commandLineString;
    commandLineString = GetCommandLineW();
    wchar_t separators[2] = L" ";
    wchar_t* part;
    part = wcstok(commandLineString,separators);
    wcscpy(part,commandLineString + wcslen(part) + 1);
    part[wcslen(part) - 1] = '\0';

    int length = wcslen(part);
    for(int i = 0; i <= length-1;i++){
        part[i] = part[i+1];

    }

    if(wStringCheck(part) == 1){
        return 1;

    }

    if(wcscmp(part,L"Manual.txt") !=0)
    if(pathType(part) == 1){
        printf("You need a absolute path!\n\n");
        return 1;

    }

    if(wcslen(part) >= MAX_PATH -1){
        printf("File name is too long!\n\n");
        return 1;

    }

    DWORD error = 0;
    HANDLE readFileHandler = NULL;
    if((readFileHandler = CreateFileW(part,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
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
            printf("Source is a directory or access is denied!\n\n");
            ExitProcess(5);
        }
        if(error == 123){
            printf("Invalid argument!\n\n");
            ExitProcess(123);

        }
        printf("CreateFileARead:%lu\n\n",error);
        ExitProcess(error);

    }

    char buffer[BLOCK];
    DWORD nrReadBytes;
    BOOL readCheck;

    while((readCheck = ReadFile(readFileHandler,buffer,BLOCK,&nrReadBytes,NULL)) == TRUE){
        for(int i = 0;i < nrReadBytes;i++){
            printf("%c",buffer[i]);

        }

        if(nrReadBytes == 0){
            break;

        }

    }

    if(readCheck == FALSE){
        error = GetLastError();
        printf("ReadCheck:%lu\n\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(readFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }


    printf("\nContent display finished!\n\n");
    return 0;

}


