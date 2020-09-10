#include "C:\Users\radut\Desktop\Aplicatii in C\Aplicatii\MAD OS Command Line\Command Line\mados.h"

int main()
{
    wchar_t firstFileFullName[MAX_PATH];
    wchar_t secondFileFullName[MAX_PATH];

    FILE* firstFile;
    FILE* secondFile;

    wchar_t line1[MAX_PATH];
    wchar_t line2[MAX_PATH];

    int lineCount1 = 0;
    int lineCount2 = 0;

    int differentLineCount = 0;

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
            printf("First file is a directory!\n\n");
            return errno;

        }

        printf("FirstFileWfopen_sError:%d\n\n",errno);
        return errno;

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
            printf("Second file is a directory!\n\n");
            return errno;

        }

        printf("SecondFileWfopen_sError:%d\n\n",errno);
        return errno;

    }

    int check1 = 0,check2 = 0;
    while(check1 == 0 && check2 == 0){
        if(fgetws(line1,MAX_PATH,firstFile) != NULL){
            lineCount1++;
            if(line1[wcslen(line1)-1] != '\n'){
                line1[wcslen(line1)] = '\n';
                line1[wcslen(line1)] = '\0';

            }

        }else{
            check1 = 1;
            break;

        }


        if(fgetws(line2,MAX_PATH,secondFile) != NULL){
            lineCount2++;
            if(line2[wcslen(line2)-1] != '\n'){
                line2[wcslen(line2)] = '\n';
                line2[wcslen(line2)+1] = '\0';

            }

        }else{
            check2 = 1;
            break;

        }

        if(wcscmp(line1,line2) != 0){
            differentLineCount++;
            wprintf(L"File1:%d.->%sFile2:%d.->%s",lineCount1,line1,lineCount2,line2);

        }

    }

    if(check1 == 1){
        printf("\nFile2+:\n");
        while(fgetws(line2,MAX_PATH,secondFile) != NULL){
            lineCount2++;
            if(line2[wcslen(line2)-1] != '\n'){
                line2[wcslen(line2)] = '\n';
                line2[wcslen(line2)+1] = '\0';

            }

            wprintf(L"%s",line2);

        }

    }

    if(check2 == 1){
        printf("\nFile1+:\n");
        wprintf(L"%s",line1);
        while(fgetws(line1,MAX_PATH,firstFile) != NULL){
            lineCount1++;
            if(line1[wcslen(line1)-1] != '\n'){
                line1[wcslen(line1)] = '\n';
                line1[wcslen(line1)+1] = '\0';

            }

            wprintf(L"%s",line1);

        }

    }


    fclose(firstFile);
    fclose(secondFile);
    printf("\nFiles were compared successfully!\n\n");

    return 0;
}
