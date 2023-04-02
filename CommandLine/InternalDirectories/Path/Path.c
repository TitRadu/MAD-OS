#include "Path.h"

void setPathDirectoryConfigurationState()
{
    if(wExist(configurationInfo.pathDirectory.path,L"") == 2){
        configurationInfo.pathDirectory.state = TRUE;

    }else
    {
        configurationInfo.pathDirectory.state = FALSE;
    }
}

void createPathDirectory()
{
    if(configurationInfo.pathDirectory.state == FALSE){
        if(createDirectory(configurationInfo.pathDirectory.path) == TRUE)
        {
            configurationInfo.pathDirectory.state = TRUE;
            printf("PATH directory was created succesfully!\n");
        }
        
    }
}

void initializePathDirectory(){
    LogA("mados", __FILE__, INFOA, __FUNCTION__);

    DWORD error = 0;
    char charPathDirectory[256] = CHAR_EMPTY_STRING;
    if(GetCurrentDirectory(sizeof(charPathDirectory), charPathDirectory) == 0)
    {
        error = GetLastError();
        printf("InitializePathDirectoryError:%lu", error);
        ExitProcess(error);
    }

    strcat_s(charPathDirectory, sizeof(charPathDirectory), "\\PATH");

    if(MultiByteToWideChar(CP_UTF8, 0, charPathDirectory, -1, configurationInfo.pathDirectory.path, 256) == 0){
        error = GetLastError();
        printf("InitializePathDirectoryError:%lu", error);
    }

    if(PathIsDirectoryEmptyW(configurationInfo.pathDirectory.path) == TRUE) 
    {
        LogA("mados", __FILE__, DBGA, "PATH directory is empty and will be removed!");
        removeDirectory(configurationInfo.pathDirectory.path);
        return;
    }

    LogA("mados", __FILE__, INFOA, "PathDirectory configuration successfully!");
}

void pathCommandSelector(PCHAR command, PWCHAR path)
{
    setPathDirectoryConfigurationState();

    if(strcmp(command, "addpath") != 0){
        if(!configurationInfo.pathDirectory.state)
        {
            printf("PATH commands are not configured!\n\n");
            return;
        }else
        {
            if(PathIsDirectoryEmptyW(configurationInfo.pathDirectory.path) == TRUE) 
            {
                printf("PATH directory is empty and will be removed!\n");
                removeDirectory(configurationInfo.pathDirectory.path);
                return;
            }
        }
    }

    if(strcmp(command, "listpath") == 0)
    {
        listPathDirectory();
    }
    if(strcmp(command, "addpath") == 0)
    {
        addFileInPathDirectory(path);
    }
    if(strcmp(command, "rpath") == 0)
    {
        removeFileFromPathDirectory();
    }
    if(strcmp(command, "Rpath") == 0)
    {
        removePathDirectory();
    }
    if(strcmp(command, "lrunpath") == 0)
    {
        runFileFromPathDirectory(TRUE);
    }
    if(strcmp(command, "runpath") == 0)
    {
        runFileFromPathDirectory(FALSE);
    }
}

void listPathDirectory()
{
    printf("\n");
    parse(configurationInfo.pathDirectory.path, L"path", NULL, INVALID_HANDLE_VALUE);
    printf("\n");
}

void addFileInPathDirectory(PWCHAR path)
{
    wchar_t filePath[MAX_PATH];
    fgetws(filePath,MAX_PATH,stdin);
    if(filePath[wcslen(filePath)-1] == '\n'){
        filePath[wcslen(filePath)-1] = '\0';
    }

    if(wStringCheck(filePath) == 1){
        return;

    }

    wchar_t* fileAbsolutePath;
    if((fileAbsolutePath = preparePathDependingOnType(path, filePath)) == NULL){
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(fileAbsolutePath,L"")) == 3){
        printf("Invalid argument!\n\n");

    }

    if(existCheck == 2){
        printf("The argument is a directory!\n\n");

    }

    if(existCheck == 0){
        printf("The argument doesn't exist as file!\n\n");

    }

    if(existCheck == 1){
        createPathDirectory();

        wStringLastPart(filePath,'\\');
        wchar_t pathDirectoryFile[1000];
        wcscpy_s(pathDirectoryFile, sizeof(pathDirectoryFile), configurationInfo.pathDirectory.path);
        wcscat_s(pathDirectoryFile, sizeof(pathDirectoryFile), L"\\");
        wcscat_s(pathDirectoryFile, sizeof(pathDirectoryFile), filePath);

        copyFile(fileAbsolutePath, pathDirectoryFile);
    }

    if(heapFreeChecker(processHeap,0, fileAbsolutePath) == FALSE){
        return;

    }
}

void removeFileFromPathDirectory()
{
    wchar_t filePath[MAX_PATH];
    fgetws(filePath,MAX_PATH,stdin);
    if(filePath[wcslen(filePath)-1] == '\n'){
        filePath[wcslen(filePath)-1] = '\0';
    }

    if(wStringCheck(filePath) == 1){
        return;

    }

    if(pathType(filePath) == ABSOLUTE_PATH){
        printf("Please insert a relativ path!\n\n");
        return;
    }

    wchar_t fileAbsolutePath[wcslen(configurationInfo.pathDirectory.path) + 1 + wcslen(filePath) + 1];
    wcscpy_s(fileAbsolutePath, sizeof(fileAbsolutePath), configurationInfo.pathDirectory.path);
    wcscat_s(fileAbsolutePath, sizeof(fileAbsolutePath), L"\\");
    wcscat_s(fileAbsolutePath, sizeof(fileAbsolutePath), filePath);

    if(removeFile(fileAbsolutePath) == 0){
        printf("PATH file was removed succesfully!\n\n");

    }else{
        return;

    }

    if(PathIsDirectoryEmptyW(configurationInfo.pathDirectory.path) == TRUE) 
    {
        printf("PATH directory is empty and will be removed!\n");
        removeDirectory(configurationInfo.pathDirectory.path);
        return;
    }

}

void removePathDirectory()
{
    if(configurationInfo.pathDirectory.state == TRUE){
        removeDirectoryRecursive(configurationInfo.pathDirectory.path, L"Rpath");
        configurationInfo.pathDirectory.state = FALSE;
    }

}

void runFileFromPathDirectory(BOOL isLocalMode)
{
    wchar_t filePath[MAX_PATH];
    fgetws(filePath,MAX_PATH,stdin);
    if(filePath[wcslen(filePath)-1] == '\n'){
        filePath[wcslen(filePath)-1] = '\0';
    }

    if(wStringCheck(filePath) == 1){
        return;

    }

    if(pathType(filePath) == ABSOLUTE_PATH){
        printf("Please insert a relativ path!\n\n");
        return;
    }

    wchar_t fileAbsolutePath[wcslen(configurationInfo.pathDirectory.path) + 1 + wcslen(filePath) + 1];
    wcscpy_s(fileAbsolutePath, sizeof(fileAbsolutePath), configurationInfo.pathDirectory.path);
    wcscat_s(fileAbsolutePath, sizeof(fileAbsolutePath), L"\\");
    wcscat_s(fileAbsolutePath, sizeof(fileAbsolutePath), filePath);

    if(wcslen(fileAbsolutePath) >= MAX_PATH -1){
        printf("Executable name is too long!\n");
        return;
    }

    int existCheck = 0;
    if((existCheck=wExist(fileAbsolutePath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 2){
        printf("The argument is a directory!\n\n");
        return;

    }

    if(existCheck == 0){
        printf("The argument doesn't exist as file!\n\n");
        return;

    }


    wchar_t argumentList[MAX_PATH];
    printf("List of arguments:");
    fgetws(argumentList,MAX_PATH,stdin);
    if(argumentList[wcslen(argumentList)-1] == '\n'){
        argumentList[wcslen(argumentList)-1] = '\0';

    }

    run(fileAbsolutePath, argumentList, isLocalMode);
  
}