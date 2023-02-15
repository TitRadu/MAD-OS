#include "D:\Proiecte C\MAD-OS\Command Line\mados.h"

int main()
{
    wchar_t firstFileFullName[MAX_PATH];
    wchar_t secondFileFullName[MAX_PATH];
    wchar_t destinationFileFullName[MAX_PATH];

    FILE* firstFile;
    FILE* secondFile;
    FILE* destinationFile;

    wchar_t line[MAX_PATH];

    int lineCount = 0;

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


    if(_wfopen_s(&firstFile,firstFileFullName,L"r") != 0){
        if(errno == ENOENT){
            printf("First file doesn't exist!\n\n");
            return errno;

        }

        if(errno == EACCES){
            printf("First file is a directory or access is denied!\n\n");
            return errno;

        }

        printf("FirstFileWfopen_sError:%d\n\n",errno);
        return errno;

    }

    int low1,high1;
    printf("First File Low Limit:");scanf("%d",&low1);fflush(stdin);
    printf("First File High Limit:");scanf("%d",&high1);fflush(stdin);
    if(low1 > high1){
        printf("Incorect limits\n\n");
        return 1;

    }

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

    if(_wfopen_s(&secondFile,secondFileFullName,L"r") != 0){
        if(errno == ENOENT){
            printf("Second file doesn't exist!\n\n");
            return errno;

        }

        if(errno == EACCES){
            printf("Second file is a directory or access is denied!\n\n");
            return errno;

        }

        printf("SecondFileWfopen_sError:%d\n\n",errno);
        return errno;

    }

    int low2,high2;
    printf("Second File Low Limit:");scanf("%d",&low2);fflush(stdin);
    printf("Second File High Limit:");scanf("%d",&high2);fflush(stdin);
    if(low2 > high2){
        printf("Incorect limits\n\n");
        return 1;

    }

    printf("Destination full name:");
    fgetws(destinationFileFullName,MAX_PATH,stdin);
    if(destinationFileFullName[wcslen(destinationFileFullName)-1] == '\n'){
        destinationFileFullName[wcslen(destinationFileFullName)-1] = '\0';

    }

    if(wStringCheck(destinationFileFullName) == 1){
        return 1;

    }

    if(pathType(destinationFileFullName) == 1){
        printf("You need a absolute path!\n");
        return 1;

    }

    if(wcslen(destinationFileFullName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

    }

    if(_wfopen_s(&destinationFile,destinationFileFullName,L"a") != 0){
        if(errno == EEXIST){
            printf("Destination file already exist!\n\n");
            return errno;

        }

        if(errno == EACCES){
            printf("Destination file is a directory or access is denied!\n\n");
            return errno;

        }

        if(errno == ENOENT){
            printf("A part from destination file isn't a directory!\n\n");
            return errno;

        }

        printf("DestinationFileWfopen_sError:%d\n\n",errno);
        return errno;

    }

    printf("\nLines from first file:\n");

    while(fgetws(line,MAX_PATH,firstFile) != NULL){
        lineCount++;
        if(low1 <= lineCount && lineCount <= high1){
            fputws(line,destinationFile);
            wprintf(L"%d.->%s",lineCount,line);

        }

    }

    printf("Lines from second file:\n");
    lineCount = 0;
    while(fgetws(line,MAX_PATH,secondFile) != NULL){
        lineCount++;
        if(low2 <= lineCount && lineCount <= high2){
            fputws(line,destinationFile);
            wprintf(L"%d.->%s",lineCount,line);

        }

    }

    fclose(firstFile);
    fclose(secondFile);
    fclose(destinationFile);
    printf("\nFiles were merged successfully!\n\n");

    return 0;
}
