#include <stdio.h>
#include <Windows.h>
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"
#include "..\..\Helpers\WcharHelper\WcharHelper.h"

int main()
{
    SetConsoleCtrlHandler(NULL,FALSE);
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return 1;

    }


    wchar_t cryptedFilePath[MAX_PATH];
    printf("Crypted file path:");
    fgetws(cryptedFilePath,MAX_PATH,stdin);
    if(cryptedFilePath[wcslen(cryptedFilePath)-1] == '\n'){
        cryptedFilePath[wcslen(cryptedFilePath)-1] = '\0';

    }

    if(wStringCheck(cryptedFilePath) == 1){
        return 1;

    }

    if(pathType(cryptedFilePath) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(cryptedFilePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    HANDLE cryptedFileHandle = NULL;
    DWORD error = 0;
    if ((cryptedFileHandle = CreateFileW(cryptedFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
        error = GetLastError();
        if (error == 2) {
            printf("The system cannot find the file specified.\n\n");
            ExitProcess(2);

        }
        if (error == 3) {
            printf("A part from crypted file path isn't a directory!\n\n");
            ExitProcess(3);

        }
        if (error == 5) {
            printf("Crypted file is a directory or access is denied!\n\n");
            ExitProcess(5);
        }
        if (error == 32) {
            printf("Other process use the file!\n\n");
            ExitProcess(32);

        }
        if (error == 123) {
            printf("Invalid argument!\n\n");
            ExitProcess(123);

        }
        printf("CreateFileWRead:%lu\n\n", error);
        ExitProcess(error);

    }

    HANDLE cryptedFileHandlerFindFirst = NULL;
    WIN32_FIND_DATAW fileInfo;
    LARGE_INTEGER fileSize;
    unsigned long long sizeInBytes = 0;
    unsigned long long remaining = 0;
    if((cryptedFileHandlerFindFirst = FindFirstFileW(cryptedFilePath,&fileInfo)) == INVALID_HANDLE_VALUE){
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

    wchar_t keyFilePath[MAX_PATH];
    wcscpy_s(keyFilePath, (wcslen(cryptedFilePath) + 1) * sizeof(wchar_t), cryptedFilePath);
    wcscat_s(keyFilePath, (wcslen(cryptedFilePath) + 4 + 1) * sizeof(wchar_t), L".key");
    if(keyFilePath[wcslen(keyFilePath)-1] == '\n'){
        keyFilePath[wcslen(keyFilePath)-1] = '\0';

    }

    if(wcslen(keyFilePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    HANDLE keyFileHandle = NULL;
    if ((keyFileHandle = CreateFileW(keyFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
        error = GetLastError();
        if (error == 2) {
            printf("The system cannot find the key file. Maybe the file isn't crypted.\n\n");
            ExitProcess(2);

        }
        if (error == 5) {
            printf("Key file is a directory,not a regular file!\n\n");
            ExitProcess(5);
        }
        if (error == 32) {
            printf("Other process use the file!\n\n");
            ExitProcess(32);

        }
        if (error == 123) {
            printf("Invalid argument!\n\n");
            ExitProcess(123);

        }

        printf("CreateFileWRead:%lu\n", error);
        ExitProcess(error);
    }

    UCHAR keyNumberBuffer[BLOCK];
    unsigned char buffer[BLOCK];
    DWORD nrReadBytes;
    DWORD nrWriteBytes;
    DWORD nrKeyWriteBytes;
    BOOL readCheck;
    BOOL writeCheck;

    while ((readCheck = ReadFile(cryptedFileHandle, buffer, BLOCK, &nrReadBytes, NULL)) == TRUE) {
        SetFilePointer(cryptedFileHandle, 0 - nrReadBytes, NULL, FILE_CURRENT);
        ReadFile(keyFileHandle, keyNumberBuffer, BLOCK, &nrKeyWriteBytes, NULL);

        for (int i = 0; i < nrReadBytes; i++) {
            buffer[i] = buffer[i] - keyNumberBuffer[i];

        }

        if ((writeCheck = WriteFile(cryptedFileHandle, buffer, nrReadBytes, &nrWriteBytes, NULL)) == FALSE) {
            error = GetLastError();
            printf("WriteCheck:%lu\n", error);
            ExitProcess(error);

        }


        if (nrReadBytes == 0) {
            break;

        }

        remaining = remaining - nrWriteBytes;
        status =((((double)sizeInBytes) - (double)remaining)/(double)sizeInBytes)*100;
        printf("\rDecrypting...%.2f%% Complete!",status);


    }

    if (CloseHandle(cryptedFileHandle) == FALSE) {
        error = GetLastError();
        ExitProcess(error);

    }
    if (CloseHandle(keyFileHandle) == FALSE) {
        error = GetLastError();
        ExitProcess(error);

    }

    if(DeleteFileW(keyFilePath) == 0){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            printf("Path is a directory or access is denied!\n");
            return ERROR_ACCESS_DENIED;
        }

        printf("RemoveFileDeleteFileError:%lu\n",error);
        return error;

    }

    printf("\nThe file was decrypted successfully!\n\n");
    return 0;

}
