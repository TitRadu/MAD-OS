#include "C:\Users\radut\Desktop\Aplicatii in C\Aplicatii\MAD OS Command Line\Command Line\mados.h"

int main()
{
    wchar_t searchString[MAX_PATH];
    wchar_t grepFileFullName[MAX_PATH];
    FILE* file;
    wchar_t line[MAX_PATH];
    int lineCount = 0;
    int appPerLine = 0;
    wchar_t* auxString;
    int position;

    printf("Search-String:");
    fgetws(searchString,MAX_PATH,stdin);
    if(searchString[wcslen(searchString)-1] == '\n'){
        searchString[wcslen(searchString)-1] = '\0';

    }

    if(wStringCheck(searchString) == 1){
        printf("\n");
        return 1;

    }

    printf("Grep-File:");
    fgetws(grepFileFullName,MAX_PATH,stdin);
    if(grepFileFullName[wcslen(grepFileFullName)-1] == '\n'){
        grepFileFullName[wcslen(grepFileFullName)-1] = '\0';

    }

    if(wStringCheck(grepFileFullName) == 1){
        printf("\n");
        return 1;


    }

    if(pathType(grepFileFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(grepFileFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    if(_wfopen_s(&file,grepFileFullName,L"r") != 0){
        if(errno == ENOENT){
            printf("Grep file doesn't exist!\n\n");
            return errno;

        }

        if(errno == EACCES){
            printf("Grep file is a directory!\n\n");
            return errno;

        }

        printf("GrepCLWfopen_sError:%d\n\n",errno);
        return errno;

    }

    while(fgetws(line,MAX_PATH,file) != NULL){
        appPerLine = 0;
        position = 0;
        lineCount++;

        while((auxString = wcsstr(line+position,searchString)) != NULL){
            appPerLine++;
            position = (int)(auxString - line + 1);


        }

        if(appPerLine!=0)
        wprintf(L"Line:%d Apparition:%d ->%s",lineCount,appPerLine,line);

    }

    fclose(file);
    printf("\n\n");

    return 0;
}
