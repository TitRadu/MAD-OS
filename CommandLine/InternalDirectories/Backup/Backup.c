#include "Backup.h"

void backupWraper(wchar_t* path){
    wchar_t backUpFileName[MAX_PATH];
    printf("File to backup:");
    fgetws(backUpFileName,MAX_PATH,stdin);
    if(backUpFileName[wcslen(backUpFileName)-1] == '\n'){
        backUpFileName[wcslen(backUpFileName)-1] = '\0';

    }

    if(wStringCheck(backUpFileName) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,backUpFileName)) == NULL){
        return;

    }

    backup(absolutePath);

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

}

void backup(wchar_t* absolutePath){
    if(wcslen(absolutePath) >= MAX_PATH - 1){
        printf("File name is too long!\n\n");
        return;

   }

    wchar_t absolutePathCopy[MAX_PATH];
    wcscpy_s(absolutePathCopy,sizeof(absolutePathCopy),absolutePath);
    wchar_t* lastPart = wStringLastPart(absolutePathCopy,'\\');

    int existCheck = 0;
    if((existCheck=wExist(absolutePath,L"")) == 0){
        printf("SourcePath doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    wchar_t backupPath[MAX_PATH];
    backupPath[0] = '\0';

    LPWSTR variableValue;
    if((variableValue = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(wchar_t)*MAX_PATH)) == NULL){
        printf("BckpHeapAllocError!\n");
        return;

    }

    GetEnvironmentVariableW(L"USERPROFILE", variableValue, MAX_PATH);
    wcscat_s(backupPath,sizeof(backupPath),variableValue);
    printf("BACKUP:");
    wcscat_s(backupPath,sizeof(backupPath),L"\\BACKUP");
    createDirectory(backupPath);

    wcscat_s(backupPath,sizeof(backupPath),L"\\");
    wcscat_s(backupPath,sizeof(backupPath),lastPart);

    if(wExist(backupPath,L"") != 0){
        printf("Backup file exists.\n\n");
        return;

    }

    if(existCheck == 1){
        copyFile(absolutePath,backupPath);
        return;

    }

    if(existCheck == 2){
        copyDirectory(absolutePath,backupPath);
        return;

    }

    if(heapFreeChecker(processHeap,0,variableValue) == FALSE){
        return;

    }

}
