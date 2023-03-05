#include "GeneralHelper.h"

void pause(){
    printf("Press enter or any key+enter to continue...\n");
    getchar();

}

int pathType(wchar_t* path){
    if(wcslen(path) >= 2){
        if(IsCharAlphaW(path[0]) != 0){
            if(path[1] == ':'){
                if(path[2] == '\\' || path[2] == '\0'){
                    return 0;

                }

            }

        }

    }

    return 1;

}

HANDLE getProcessHeapChecker(){
    HANDLE heap = NULL;
    DWORD error = 0;
    if((heap = GetProcessHeap()) == NULL){
        error = GetLastError();
        printf("GetProcessHeapCheckerError:%lu\n",error);
        return NULL;

    }

    return heap;

}

int heapFreeChecker(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem){
    DWORD error = 0;
    if(HeapFree(hHeap,dwFlags,lpMem) == FALSE){
        error = GetLastError();
        printf("HeapFreeError:%lu\n",error);
        return FALSE;

    }

    return TRUE;

}

int allSpaces(char* string){
    for(int i = 0;i < strlen(string);i++){
        if(string[i] != 32){
            return 0;

        }
    }

    return 1;
}

int stringCheck(char* string){
    if(strcmp(string,"") == 0 || allSpaces(string) == 1){
        printf("Argument is empty or contains only spaces!\n");
        return 1;

    }

    return 0;

}