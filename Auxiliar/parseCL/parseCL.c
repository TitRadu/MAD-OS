#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void parseCL(wchar_t* path,char control,int* numberOfFiles,int* numberOfDirectories,int* numberOfDeniedFiles){
    HANDLE hd;
    WIN32_FIND_DATAW fileInfo;
    SYSTEMTIME fileLastWriteTime;
    LARGE_INTEGER fileSize;
    wchar_t starPath[MAX_PATH];
    starPath[0] = '\0';
    wcscat_s(starPath,sizeof(starPath),path);
    wcscat_s(starPath,sizeof(starPath),L"\\*");
    wchar_t newPath[MAX_PATH];
    newPath[0] = '\0';

    float sizeMB = 0;

    DWORD error = 0;
    if((hd = FindFirstFileW(starPath,&fileInfo)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            (*numberOfDeniedFiles)++;
            printf("-\tAcces to this file is denied!\n");
            return;

        }
        printf("Error:%lu\n",error);
        return;


    }

    do{
        if((wcscmp(fileInfo.cFileName,L".") == 0) || (wcscmp(fileInfo.cFileName,L"..") == 0)){
            continue;

        }

        snwprintf(newPath,1024,L"%s\\%s",path,fileInfo.cFileName);

        if(FileTimeToSystemTime(&fileInfo.ftLastWriteTime,&fileLastWriteTime) == 0){
            error = GetLastError();
            printf("Error:%lu\n",error);

        }

        fileSize.LowPart = fileInfo.nFileSizeLow;
        fileSize.HighPart = fileInfo.nFileSizeHigh;
        sizeMB = (float)fileSize.QuadPart / ((float)1024*(float)1024);

        if(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            (*numberOfDirectories)++;
            wprintf(L"D\t%.3f\t\t%02d/%02d %02d:%02d:%02d %04d \t%s\n",sizeMB,fileLastWriteTime.wMonth,fileLastWriteTime.wDay,fileLastWriteTime.wHour,fileLastWriteTime.wMinute,fileLastWriteTime.wSecond,fileLastWriteTime.wYear,newPath);
            if(control == 'r' || control == 'R'){
                parseCL(newPath,control,numberOfFiles,numberOfDirectories,numberOfDeniedFiles);
            }
            if(control == 'R'){
                if(RemoveDirectoryW(newPath) == 0){
                    error = GetLastError();
                    wprintf(L"Error:%lu---%s\n",error,newPath);
                    ExitProcess(1);

                }

            }

            continue;
        }
        (*numberOfFiles)++;
        wprintf(L"F\t%.3f\t\t%02d/%02d %02d:%02d:%02d %04d \t%s\n",sizeMB,fileLastWriteTime.wMonth,fileLastWriteTime.wDay,fileLastWriteTime.wHour,fileLastWriteTime.wMinute,fileLastWriteTime.wSecond,fileLastWriteTime.wYear,newPath);
        if(control == 'R'){
            if(DeleteFileW(newPath) == 0){
                error = GetLastError();
                printf("Error:%lu\n",error);
                ExitProcess(1);

            }

        }

    }
    while(FindNextFileW(hd,&fileInfo) != 0);


    if(FindClose(hd) == FALSE){
        error = GetLastError();
        printf("FindCloseError:%lu\n",error);
        ExitProcess(error);

    }

}



int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    LPWSTR commandLineString;
    commandLineString = GetCommandLineW();
    wchar_t separators[2] = L"\"";
    wchar_t* part;
    part = wcstok(commandLineString,separators);
    part = wcstok(NULL,separators);
    part = wcstok(NULL,separators);

    int numberOfFiles = 0;
    int numberOfDirectories = 0;
    int numberOfDeniedFiles = 0;
    printf("Type\tSize(MB)\tModified\t\t\tPath\n");
    parseCL(part,argv[2][0],&numberOfFiles,&numberOfDirectories,&numberOfDeniedFiles);
    printf("Directory statistics: Files:%d   Directories:%d   DeniedFiles:%d\n",numberOfFiles,numberOfDirectories,numberOfDeniedFiles);


    return 0;
}


