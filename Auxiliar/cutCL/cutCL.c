#include <stdio.h>
#include <Windows.h>
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"
#include "..\..\Helpers\WcharHelper\WcharHelper.h"

int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return 1;

    }

    wchar_t sourceFullName[MAX_PATH];
    wchar_t destinationFullName[MAX_PATH];

    printf("Source full name:");
    fgetws(sourceFullName,MAX_PATH,stdin);
    if(sourceFullName[wcslen(sourceFullName)-1] == '\n'){
        sourceFullName[wcslen(sourceFullName)-1] = '\0';

    }

    if(wStringCheck(sourceFullName) == 1){
        return 1;

    }

    if(pathType(sourceFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(sourceFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    DWORD error = 0;

    LPOFSTRUCT fileInformation;
    if((fileInformation = (LPOFSTRUCT)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(OFSTRUCT))) == NULL){
        printf("HeapAllocError!\n");
        return 1;

    }

    HANDLE readFileHandler = NULL;
    if((readFileHandler = CreateFileW(sourceFullName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
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
        printf("CreateFileARead:%lu\n",error);
        ExitProcess(error);

    }

    HANDLE readFileHandlerFindFirst = NULL;
    WIN32_FIND_DATAW fileInfo;
    LARGE_INTEGER fileSize;
    unsigned long long sizeInBytes = 0;
    unsigned long long remaining = 0;
    if((readFileHandlerFindFirst = FindFirstFileW(sourceFullName,&fileInfo)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            printf("-\tAcces to this file is denied!\n");
            return 1;

        }
        printf("FindFirstFileError:%lu\n",error);
        return 1;


    }

    fileSize.LowPart = fileInfo.nFileSizeLow;
    fileSize.HighPart = fileInfo.nFileSizeHigh;
    sizeInBytes = fileSize.QuadPart;
    remaining = sizeInBytes;
    double status = 0;

    printf("Destination full name:");

    fgetws(destinationFullName,MAX_PATH,stdin);
    if(destinationFullName[wcslen(destinationFullName)-1] == '\n'){
        destinationFullName[wcslen(destinationFullName)-1] = '\0';

    }

    if(wStringCheck(destinationFullName) == 1){
        return 1;

    }

    if(pathType(destinationFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(destinationFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    HANDLE writeFileHandler = NULL;
    if((writeFileHandler = CreateFileW(destinationFullName,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
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

        printf("CreateFileAWrite:%lu\n",error);
        ExitProcess(error);

    }

    LPVOID buffer;
    if((buffer = (LPVOID)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,BLOCK)) == NULL){
        printf("HeapAllocError!\n");
        return 1;

    }
    PDWORD nrReadBytes;
    if((nrReadBytes = (PDWORD)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(DWORD))) == NULL){
        printf("HeapAllocError!\n");
        return 1;

    }
    PDWORD nrWriteBytes;
    if((nrWriteBytes = (PDWORD)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(DWORD))) == NULL){
        printf("HeapAllocError!\n");
        return 1;

    }
    BOOL readCheck;
    BOOL writeCheck;
    while((readCheck = ReadFile(readFileHandler,buffer,BLOCK,nrReadBytes,NULL)) == TRUE){
        if((writeCheck = WriteFile(writeFileHandler,buffer,*nrReadBytes,nrWriteBytes,NULL)) ==FALSE){
            error = GetLastError();
            printf("WriteCheck:%lu\n",error);
            ExitProcess(error);
        }


        if(*nrReadBytes == 0){
            break;

        }

        remaining = remaining - *nrWriteBytes;
        status =((((double)sizeInBytes) - (double)remaining)/(double)sizeInBytes)*100;
        printf("\rCopying...%.2f%% Complete!",status);

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

    if(FindClose(readFileHandlerFindFirst) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(CloseHandle(writeFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(heapFreeChecker(processHeap,0,fileInformation) == FALSE){
        return 1;

    }

    if(heapFreeChecker(processHeap,0,buffer) == FALSE){
        return 1;

    }

    if(heapFreeChecker(processHeap,0,nrReadBytes) == FALSE){
        return 1;

    }

    if(heapFreeChecker(processHeap,0,nrWriteBytes) == FALSE){
        return 1;

    }

    printf("\nThe file was copying successfully!\n");
    error = 0;
    if(DeleteFileW(sourceFullName) == FALSE){
        error = GetLastError();
        printf("DeleteFileCheck:%lu\n",error);
        ExitProcess(-1);

    }
    printf("The source file was deleted successfully!\n\n");

    return 0;

}
