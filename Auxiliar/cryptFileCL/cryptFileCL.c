#include "D:\Proiecte C\MAD-OS\Command Line\mados.h"

void getRandomNumber(BCRYPT_ALG_HANDLE algorithmHandle, PUCHAR receiveRandomNumberBuffer, ULONG bufferSize) {
    NTSTATUS error = 0;
    if ((error = BCryptGenRandom(algorithmHandle, receiveRandomNumberBuffer, bufferSize, 0)) != CMC_STATUS_SUCCESS) {
        printf("GetRandomNumberBCryptGenRandomError:%lu\n", error);
        ExitProcess(error);

    }

}

int main(){
    SetConsoleCtrlHandler(NULL,FALSE);
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return 1;

    }

    wchar_t sourceFilePath[MAX_PATH];
    printf("Source file path:");
    fgetws(sourceFilePath,MAX_PATH,stdin);
    if(sourceFilePath[wcslen(sourceFilePath)-1] == '\n'){
        sourceFilePath[wcslen(sourceFilePath)-1] = '\0';

    }

    if(wStringCheck(sourceFilePath) == 1){
        return 1;

    }

    if(pathType(sourceFilePath) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(sourceFilePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    DWORD error = 0;
    HANDLE sourceFileHandle = NULL;
    if ((sourceFileHandle = CreateFileW(sourceFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
        error = GetLastError();
        if (error == 2) {
            printf("The system cannot find the file specified.\n\n");
            ExitProcess(2);

        }
        if (error == 3) {
            printf("A part from source path isn't a directory!\n\n");
            ExitProcess(3);

        }
        if (error == 5) {
            printf("Source is a directory,not a regular file!\n\n");
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

    HANDLE sourceFileHandlerFindFirst = NULL;
    WIN32_FIND_DATAW fileInfo;
    LARGE_INTEGER fileSize;
    unsigned long long sizeInBytes = 0;
    unsigned long long remaining = 0;
    if((sourceFileHandlerFindFirst = FindFirstFileW(sourceFilePath,&fileInfo)) == INVALID_HANDLE_VALUE){
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
    wcscpy_s(keyFilePath, (wcslen(sourceFilePath) + 1) * sizeof(wchar_t), sourceFilePath);
    wcscat_s(keyFilePath, (wcslen(sourceFilePath) + 4 + 1) * sizeof(wchar_t), L".key");
    if(keyFilePath[wcslen(keyFilePath)-1] == '\n'){
        keyFilePath[wcslen(keyFilePath)-1] = '\0';

    }

    if(wcslen(keyFilePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    HANDLE keyFileHandle = NULL;
    if ((keyFileHandle = CreateFileW(keyFilePath, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN, NULL)) == INVALID_HANDLE_VALUE) {
        error = GetLastError();
        if (error == 80) {
            printf("(Key path)The file exists. It is possible that this file is the key file!\n");
            ExitProcess(80);

        }
        if (error == 5) {
            printf("Key path is a directory or access is denied!\n");
            ExitProcess(5);
        }
        if (error == 123) {
            printf("Key file path is invalid!\n");
            ExitProcess(123);

        }

        printf("CreateFileWWrite:%lu\n", error);
        ExitProcess(error);
    }

    NTSTATUS ntError = 0;
    BCRYPT_ALG_HANDLE algorithmHandle;
    if ((ntError = BCryptOpenAlgorithmProvider(&algorithmHandle, BCRYPT_RNG_ALGORITHM, NULL, 0)) != CMC_STATUS_SUCCESS) {
        printf("BCryptOpenAlgorithmProviderError:%ld\n", error);
        ExitProcess(error);

    }

    UCHAR randomNumber;
    unsigned char buffer[BLOCK];
    DWORD nrReadBytes;
    DWORD nrWriteBytes;
    BOOL readCheck;
    BOOL writeCheck;

    while ((readCheck = ReadFile(sourceFileHandle, buffer, BLOCK, &nrReadBytes, NULL)) == TRUE) {
        SetFilePointer(sourceFileHandle, 0-nrReadBytes, NULL, FILE_CURRENT);

        for (int i = 0; i < nrReadBytes; i++) {
            getRandomNumber(algorithmHandle, &randomNumber, sizeof(UCHAR));
            buffer[i] = buffer[i] + randomNumber;
            WriteFile(keyFileHandle, &randomNumber, sizeof(UCHAR), NULL, NULL);


        }
        if ((writeCheck = WriteFile(sourceFileHandle, buffer, nrReadBytes, &nrWriteBytes, NULL)) == FALSE) {
            error = GetLastError();
            printf("WriteCheck:%lu\n", error);
            ExitProcess(error);

        }


        if (nrReadBytes == 0) {
            break;

        }

        remaining = remaining - nrWriteBytes;
        status =((((double)sizeInBytes) - (double)remaining)/(double)sizeInBytes)*100;
        printf("\rCrypting...%.2f%% Complete!",status);

    }

    if (CloseHandle(sourceFileHandle) == FALSE) {
        error = GetLastError();
        ExitProcess(error);

    }
    if (CloseHandle(keyFileHandle) == FALSE) {
        error = GetLastError();
        ExitProcess(error);

    }
    if ((ntError = BCryptCloseAlgorithmProvider(algorithmHandle, 0)) != CMC_STATUS_SUCCESS){
        printf("BCryptCloseAlgorithmProviderError:%ld\n", error);
        ExitProcess(error);

    }

    printf("\nThe file was crypted successfully!\n\n");
    return 0;

}
