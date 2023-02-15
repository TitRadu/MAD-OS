#include "D:\Proiecte C\MAD-OS\Command Line\mados.h"

int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return 1;

    }

    wchar_t firstFileFullName[MAX_PATH];
    wchar_t secondFileFullName[MAX_PATH];
    wchar_t destinationFullName[MAX_PATH];
    WIN32_FIND_DATAW fileInfo;
    LARGE_INTEGER fileSize;
    double status = 0;

    printf("First File full name:");
    fgetws(firstFileFullName,MAX_PATH,stdin);
    if(firstFileFullName[wcslen(firstFileFullName)-1] == '\n'){
        firstFileFullName[wcslen(firstFileFullName)-1] = '\0';

    }

    if(wStringCheck(firstFileFullName) == 1){
        return 1;

    }

    if(pathType(firstFileFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(firstFileFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    DWORD error = 0;

    LPOFSTRUCT fileInformation;
    if((fileInformation = (LPOFSTRUCT)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(OFSTRUCT))) == NULL){
        printf("HeapAllocError!\n");
        return 1;

    }

    HANDLE firstFileHandler = NULL;
    if((firstFileHandler = CreateFileW(firstFileFullName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == 2){
            printf("The system cannot find the file specified.\n");
            ExitProcess(2);

        }
        if(error == 3){
            printf("A part from first file path isn't a directory!\n");
            ExitProcess(3);

        }
        if(error == 5){
            printf("First file is a directory or access is denied!\n");
            ExitProcess(5);
        }
        if(error == 123){
            printf("First file path is invalid!\n");
            ExitProcess(123);

        }
        printf("FirstFileCreateFileW:%lu\n",error);
        ExitProcess(error);

    }

    HANDLE fileHandlerFindFirst = NULL;
    if((fileHandlerFindFirst = FindFirstFileW(firstFileFullName,&fileInfo)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            printf("-\tAcces to this file is denied!\n");
            return 1;

        }
        printf("FirstFileFindFirstFileError:%lu\n",error);
        return 1;


    }

    fileSize.LowPart = fileInfo.nFileSizeLow;
    fileSize.HighPart = fileInfo.nFileSizeHigh;
    unsigned long long sizeInBytes1 = fileSize.QuadPart;
    unsigned long long remaining1 = sizeInBytes1;

    printf("Second File full name:");
    fgetws(secondFileFullName,MAX_PATH,stdin);
    if(secondFileFullName[wcslen(secondFileFullName)-1] == '\n'){
        secondFileFullName[wcslen(secondFileFullName)-1] = '\0';

    }

    if(wStringCheck(secondFileFullName) == 1){
        return 1;

    }

    if(pathType(secondFileFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(secondFileFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    error = 0;

    if(heapFreeChecker(processHeap,0,fileInformation) == FALSE){
        return 1;

    }
    fileInformation = NULL;
    if((fileInformation = (LPOFSTRUCT)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(OFSTRUCT))) == NULL){
        printf("HeapAllocError!\n");
        return 1;

    }

    HANDLE secondFileHandler = NULL;
    if((secondFileHandler = CreateFileW(secondFileFullName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == 2){
            printf("The system cannot find the file specified.\n");
            ExitProcess(2);

        }
        if(error == 3){
            printf("A part from second file path isn't a directory!\n");
            ExitProcess(3);

        }
        if(error == 5){
            printf("Second file is a directory or access is denied!\n");
            ExitProcess(5);
        }
        if(error == 123){
            printf("Second file path is invalid!\n");
            ExitProcess(123);

        }
        printf("SecondFileCreateFileW:%lu\n",error);
        ExitProcess(error);

    }

    if(FindClose(fileHandlerFindFirst) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }
    fileHandlerFindFirst = NULL;
    if((fileHandlerFindFirst = FindFirstFileW(secondFileFullName,&fileInfo)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            printf("-\tAcces to this file is denied!\n");
            return 1;

        }
        printf("SecondFileFindFirstFileError:%lu\n",error);
        return 1;


    }

    fileSize.LowPart = fileInfo.nFileSizeLow;
    fileSize.HighPart = fileInfo.nFileSizeHigh;
    unsigned long long sizeInBytes2 = fileSize.QuadPart;
    unsigned long long remaining2 = sizeInBytes2;

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

    HANDLE destinationFileHandler = NULL;
    if((destinationFileHandler = CreateFileW(destinationFullName,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
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

        printf("DestinationFileCreateFileW:%lu\n",error);
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

    printf("\nSize of first file:%.3f\n",(float)sizeInBytes1/((float)1024*(float)1024));
    while((readCheck = ReadFile(firstFileHandler,buffer,BLOCK,nrReadBytes,NULL)) == TRUE){
        if((writeCheck = WriteFile(destinationFileHandler,buffer,*nrReadBytes,nrWriteBytes,NULL)) ==FALSE){
            error = GetLastError();
            printf("WriteCheck2:%lu\n",error);
            ExitProcess(error);
        }


        if(*nrReadBytes == 0){
            break;

        }

        remaining1 = remaining1 - *nrWriteBytes;
        status =((((double)sizeInBytes1) - (double)remaining1)/(double)sizeInBytes1)*100;
        printf("\rCopying first file...%.2f%% Complete!",status);

    }

    if(readCheck == FALSE){
        error = GetLastError();
        printf("ReadCheck2:%lu\n",error);
        ExitProcess(error);

    }

    printf("\nSize of first file:%.3f\n",(float)sizeInBytes2/((float)1024*(float)1024));
    while((readCheck = ReadFile(secondFileHandler,buffer,BLOCK,nrReadBytes,NULL)) == TRUE){
        if((writeCheck = WriteFile(destinationFileHandler,buffer,*nrReadBytes,nrWriteBytes,NULL)) ==FALSE){
            error = GetLastError();
            printf("WriteCheck2:%lu\n",error);
            ExitProcess(error);
        }


        if(*nrReadBytes == 0){
            break;

        }

        remaining2 = remaining2 - *nrWriteBytes;
        status =((((double)sizeInBytes2) - (double)remaining2)/(double)sizeInBytes2)*100;
        printf("\rCopying second file...%.2f%% Complete!",status);

    }

    if(readCheck == FALSE){
        error = GetLastError();
        printf("ReadCheck2Error:%lu\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(firstFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(CloseHandle(secondFileHandler) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(FindClose(fileHandlerFindFirst) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(CloseHandle(destinationFileHandler) == FALSE){
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

    printf("\nFiles were merged successfully!\n\n");

}
