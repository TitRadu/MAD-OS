#include "WcharHelper.h"

void wStringInQuatationMarks(wchar_t* string){
    wchar_t newString[wcslen(string)+3];
    newString[0] = '\0';
    wcscat_s(newString,sizeof(newString),L"\"");
    wcscat_s(newString,sizeof(newString),string);
    wcscat_s(newString,sizeof(newString),L"\"");
    wcscpy(string,newString);

}

int wExist(wchar_t* path,wchar_t *name){
    wchar_t newpath[PATH];
    _snwprintf(newpath,PATH,L"%s%s",path,name);

    DWORD fileType = 0;

    DWORD error = 0;
    if( (fileType=GetFileAttributesW(newpath)) == INVALID_FILE_ATTRIBUTES){
        error = GetLastError();

        if(error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND){
            return 0;

        }

        if(error == ERROR_INVALID_NAME){
            return 3;

        }

        printf("WExistGetFileAttributesError:%lu\n",error);
        ExitProcess(-1);

    }

    if(((fileType >> 4) & 1) == 1){
        return 2;

    }

    return 1;

}

int wAllSpaces(wchar_t* string){
    for(int i = 0;i < wcslen(string);i++){
        if(string[i] != 32){
            return 0;

        }
    }

    return 1;
}

int wStringCheck(wchar_t* string){
    if(wcscmp(string,L"") == 0 || wAllSpaces(string) == 1){
        printf("Argument is empty or contains only spaces!\n");
        return 1;

    }

    return 0;

}

wchar_t* wStringWithoutLast(wchar_t* string,wchar_t c){
    int index = 0;
    index = wLastAparition(string,c);

    if(index != -1){
        string[index] = '\0';
    }
    else{
        string = NULL;

    }

    return string;
}

wchar_t* wStringLastPart(wchar_t* string,wchar_t c){
    int index = 0;
    index = wLastAparition(string,c);

    if(index != -1){
        wcscpy_s(string,sizeof(wchar_t)*MAX_PATH,string+index);
    }
    else{
        string = NULL;

    }

    return string;

}

int wNumberOfAparition(wchar_t* string,wchar_t c){
    int index = 0;
    int i;
    for(i=0;i<wcslen(string);i++){

        if(string[i] == c){
            index = index + 1;
        }
    }

    return index;
}

int wLastAparition(wchar_t *string,wchar_t c){
    int index = -1;
    int i;
    for(i=0;i<wcslen(string);i++){

        if(string[i] == c){
            index = i;
        }
    }

    return index;
}