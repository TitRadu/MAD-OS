#include "Navigator.h"

void changePath(wchar_t *path){
    wchar_t changePath[MAX_PATH];
    fgetws(changePath,MAX_PATH,stdin);
    if(changePath[wcslen(changePath)-1] == '\n'){
        changePath[wcslen(changePath)-1] = '\0';
    }

    if(wStringCheck(changePath) == 1){
        return;

    }


    wchar_t absolutePath[MAX_PATH];

    if(pathType(changePath) == 0){
        wcscpy_s(absolutePath,sizeof(absolutePath),changePath);

    }else{
        wcscpy_s(absolutePath,sizeof(absolutePath),path);
        wcscat_s(absolutePath,sizeof(absolutePath),changePath);

    }

    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(absolutePath,L"")) == 0){
        printf("This path doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck != 2){
        printf("This path isn't a directory!\n");
        return;

    }


    wcscpy_s(path,MAX_PATH*sizeof(wchar_t),absolutePath);
    if(wcslen(path) != 3){
        wcscat_s(path,MAX_PATH*sizeof(wchar_t),L"\\");

    }

}

void back(wchar_t* path){
    if(wNumberOfAparition(path,'\\') < 2){
        return;

    }

    path[wcslen(path)-1] = '\0';
    int index = 0;
    if((index = wLastAparition(path,'\\')) < 0){
        printf("BackLastAparitionError:Error\n");
        ExitProcess(-1);

    }
    path[index+1] = '\0';

}

PWCHAR preparePathDependingOnType(PWCHAR path, PWCHAR checkPath){
    PWCHAR absolutePath;
    if((absolutePath = (wchar_t*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(wchar_t)*MAX_PATH)) == NULL){
        printf("PreparePathDepedingOnTypeHeapAllocError!\n");
        return NULL;

    }

    if(pathType(checkPath) == ABSOLUTE_PATH){
        wcscpy_s(absolutePath,sizeof(wchar_t)*MAX_PATH,checkPath);

    }else{
        wcscpy_s(absolutePath,sizeof(wchar_t)*MAX_PATH,path);
        wcscat_s(absolutePath,sizeof(wchar_t)*MAX_PATH,checkPath);

    }

    return absolutePath;

}