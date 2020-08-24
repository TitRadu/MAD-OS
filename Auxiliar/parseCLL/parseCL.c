#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void parse(wchar_t* path,char control,int* numberOfFiles,int* numberOfDirectories,int* numberOfDeniedFiles){
    HANDLE hd;
    WIN32_FIND_DATAW fileInfo;
    SYSTEMTIME fileLastWriteTime;
    LARGE_INTEGER fileSize;
    wchar_t* starPath[MAX_PATH];
    starPath[0] = '\0';
    strcat(starPath,path);
    strcat(starPath,"\\*");
    char newPath[1024];
    newPath[0] = '\0';

    float sizeMB = 0;

    DWORD error = 0;
    if((hd = FindFirstFile(starPath,&fileInfo)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            (*numberOfDeniedFiles)++;
            printf("-\tAcces to this file is denied!\n");
            return;

        }
        printf("Error:%d\n",error);
        return;


    }

    do{
        if((strcmp(fileInfo.cFileName,".") == 0) || (strcmp(fileInfo.cFileName,"..") == 0)){
            continue;

        }

        snprintf(newPath,1024,"%s\\%s",path,fileInfo.cFileName);

        if(FileTimeToSystemTime(&fileInfo.ftLastWriteTime,&fileLastWriteTime) == 0){
            error = GetLastError();
            printf("Error:%d\n",error);

        }

        fileSize.LowPart = fileInfo.nFileSizeLow;
        fileSize.HighPart = fileInfo.nFileSizeHigh;
        sizeMB = (float)fileSize.QuadPart / ((float)1024*(float)1024);

        if(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            (*numberOfDirectories)++;
            printf("D\t%.3f\t\t%02d/%02d %02d:%02d:%02d %04d \t%s\n",sizeMB,fileLastWriteTime.wMonth,fileLastWriteTime.wDay,fileLastWriteTime.wHour,fileLastWriteTime.wMinute,fileLastWriteTime.wSecond,fileLastWriteTime.wYear,newPath);
            if(control == 'r' || control == 'R'){
                parse(newPath,control,numberOfFiles,numberOfDirectories,numberOfDeniedFiles);
            }
            if(control == 'R'){
                if(RemoveDirectory(newPath) == 0){
                    error = GetLastError();
                    printf("Error:%d---%s\n",error,newPath);
                    ExitProcess(1);

                }

            }

            continue;
        }
        (*numberOfFiles)++;
        printf("F\t%.3f\t\t%02d/%02d %02d:%02d:%02d %04d \t%s\n",sizeMB,fileLastWriteTime.wMonth,fileLastWriteTime.wDay,fileLastWriteTime.wHour,fileLastWriteTime.wMinute,fileLastWriteTime.wSecond,fileLastWriteTime.wYear,newPath);
        if(control == 'R'){
            if(DeleteFile(newPath) == 0){
                error = GetLastError();
                printf("Error:%d\n");
                ExitProcess(1);

            }

        }

    }
    while(FindNextFile(hd,&fileInfo) != 0);


    if(FindClose(hd) == FALSE){
        error = GetLastError();
        printf("FindCloseError:%d\n",error);
        ExitProcess(error);

    }

}



int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    int numberOfFiles = 0;
    int numberOfDirectories = 0;
    int numberOfDeniedFiles = 0;
    printf("Type\tSize(MB)\tModified\t\t\tPath\n");
    parse(argv[1],argv[2][0],&numberOfFiles,&numberOfDirectories,&numberOfDeniedFiles);
    printf("Directory statistics: Files:%d   Directories:%d   DeniedFiles:%d\n",numberOfFiles,numberOfDirectories,numberOfDeniedFiles);

    return 0;
}


