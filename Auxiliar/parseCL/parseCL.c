#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void parseCL(wchar_t* directoryPath, PWCHAR control, int* numberOfFiles, int* numberOfDirectories, int* numberOfDeniedFiles){
    HANDLE hd;
    WIN32_FIND_DATAW fileInfo;
    SYSTEMTIME fileLastWriteTime;
    LARGE_INTEGER fileSize;
    wchar_t starPath[MAX_PATH];
    starPath[0] = '\0';
    wcscat_s(starPath,sizeof(starPath),directoryPath);
    wcscat_s(starPath,sizeof(starPath),L"\\*");
    wchar_t fileNameForPrint[MAX_PATH];
    fileNameForPrint[0] = '\0';
    wchar_t filePath[MAX_PATH];
    filePath[0] = '\0';

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

        if(wcscmp(control, L"path") == 0 || wcscmp(control, L"Rpath") == 0)
        {
            wcscpy_s(fileNameForPrint, sizeof(fileNameForPrint), fileInfo.cFileName);
        }else{
            snwprintf(fileNameForPrint,1024,L"%s\\%s",directoryPath,fileInfo.cFileName);
        }

        if(wcscmp(control, L"r") == 0 || wcscmp(control, L"R") == 0 || wcscmp(control, L"Rpath") == 0)
        {
            snwprintf(filePath,1024,L"%s\\%s",directoryPath,fileInfo.cFileName);
        }

        if(FileTimeToSystemTime(&fileInfo.ftLastWriteTime,&fileLastWriteTime) == 0){
            error = GetLastError();
            printf("Error:%lu\n",error);

        }

        fileSize.LowPart = fileInfo.nFileSizeLow;
        fileSize.HighPart = fileInfo.nFileSizeHigh;
        sizeMB = (float)fileSize.QuadPart / ((float)1024*(float)1024);

        if(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            (*numberOfDirectories)++;
            wprintf(L"D\t%.3f\t\t%02d/%02d %02d:%02d:%02d %04d \t%s\n",sizeMB,fileLastWriteTime.wMonth,fileLastWriteTime.wDay,fileLastWriteTime.wHour,fileLastWriteTime.wMinute,fileLastWriteTime.wSecond,fileLastWriteTime.wYear,fileNameForPrint);
            if((wcscmp(control, L"r") == 0) || (wcscmp(control, L"R") == 0) || (wcscmp(control, L"Rpath") == 0)){
                parseCL(filePath,control,numberOfFiles,numberOfDirectories,numberOfDeniedFiles);
            }
            if(wcscmp(control, L"R") == 0 || wcscmp(control, L"Rpath") == 0){
                if(RemoveDirectoryW(filePath) == 0){
                    error = GetLastError();
                    wprintf(L"Error:%lu---%s\n",error,filePath);
                    ExitProcess(1);

                }

            }

            continue;
        }
        (*numberOfFiles)++;
        wprintf(L"F\t%.3f\t\t%02d/%02d %02d:%02d:%02d %04d \t%s\n",sizeMB,fileLastWriteTime.wMonth,fileLastWriteTime.wDay,fileLastWriteTime.wHour,fileLastWriteTime.wMinute,fileLastWriteTime.wSecond,fileLastWriteTime.wYear,fileNameForPrint);
        if(wcscmp(control, L"R") == 0 || wcscmp(control, L"Rpath") == 0){
            if(DeleteFileW(filePath) == 0){
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

    DWORD error = 0;
    WCHAR directoryPath[MAX_PATH];
    if(MultiByteToWideChar(CP_UTF8, 0, argv[1], -1, directoryPath, MAX_PATH) == 0){
        error = GetLastError();
        printf("ParseCLMultiByteToWideCharDirectoryPathError:%lu\n", error);
    }

    WCHAR control[30];
    if(MultiByteToWideChar(CP_UTF8, 0, argv[2], -1, control, 30) == 0){
        error = GetLastError();
        printf("ParseCLMultiByteToWideCharControlError:%lu\n", error);
    }

    int numberOfFiles = 0;
    int numberOfDirectories = 0;
    int numberOfDeniedFiles = 0;
    if(wcscmp(control, L"path") == 0 || wcscmp(control, L"Rpath") == 0){
        printf("Type\tSize(MB)\tModified\t\tFile\n");
    }else{
        printf("Type\tSize(MB)\tModified\t\tPath\n");
    }
    parseCL(directoryPath, control, &numberOfFiles, &numberOfDirectories, &numberOfDeniedFiles);
    printf("Directory statistics: Files:%d   Directories:%d   DeniedFiles:%d\n",numberOfFiles,numberOfDirectories,numberOfDeniedFiles);


    return 0;
}


