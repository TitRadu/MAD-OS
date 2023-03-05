#include "InternalRunner.h"

void cline(BOOL isLocalMode){
    if(isLocalMode){
        forkk(L"Command Line.exe",L"", INVALID_HANDLE_VALUE);  
    }else
    {
        HINSTANCE error; 
        if((error = ShellExecuteW(NULL,L"open",L"Command Line.exe",NULL,NULL,1)) <= (HINSTANCE)32){
            printf("ClineShellExecuteError:%p\n", error);
            return;

        }
    }

}

void newCline(){
    if((ShellExecuteW(NULL,L"open",L"Command Line.exe",NULL,NULL,1)) <= (HINSTANCE)32){
        printf("Error!\n");
        return;

    }

    ExitProcess(0);
}

void sortFilesWraper(wchar_t* path){
    wchar_t sortDirectoryPath[MAX_PATH];
    printf("Sort-Path:");
    fgetws(sortDirectoryPath,MAX_PATH,stdin);
    if(sortDirectoryPath[wcslen(sortDirectoryPath)-1] == '\n'){
        sortDirectoryPath[wcslen(sortDirectoryPath)-1] = '\0';
    }

    if(wStringCheck(sortDirectoryPath) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,sortDirectoryPath)) == NULL){
        return;

    }

    sortFiles(absolutePath);

}

void sortFiles(wchar_t* sortDirectoryPath){
    wchar_t* arguments;
    if((arguments = (wchar_t*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,4+wcslen(sortDirectoryPath)*sizeof(wchar_t)+2+2)) == NULL){
            printf("SortFilesHeapAllocError!\n");
            ExitProcess(1);

    }

    wcscpy_s(arguments,8+wcslen(sortDirectoryPath)*sizeof(wchar_t)+2+2,L"\"");
    wcscat_s(arguments,8+wcslen(sortDirectoryPath)*sizeof(wchar_t)+2+2,sortDirectoryPath);
    wcscat_s(arguments,8+wcslen(sortDirectoryPath)*sizeof(wchar_t)+2+2,L"\"");

    forkk(L"sortFilesCL.exe",arguments, INVALID_HANDLE_VALUE);

}


void sortDirectory(){
    forkk(L"sortDirCL.exe",L"", INVALID_HANDLE_VALUE);

}

void myCopyFile(char* control){
    if(strcmp(control,"copy") == 0)
    forkk(L"copyCL.exe",L"", INVALID_HANDLE_VALUE);

    if(strcmp(control,"cut") == 0)
    forkk(L"cutCL.exe",L"", INVALID_HANDLE_VALUE);

}

void generateFile(){
    forkk(L"fileGeneratorCL.exe",L"", INVALID_HANDLE_VALUE);

}

void cryptFile(){
    forkk(L"cryptFileCL.exe",L"", INVALID_HANDLE_VALUE);

}

void decryptFile(){
    forkk(L"decryptFileCL.exe",L"", INVALID_HANDLE_VALUE);

}

void fileContentWraper(){
    wchar_t contentFileFullName[PATH];
    printf("File-Path:");
    fgetws(contentFileFullName,MAX_PATH,stdin);
    if(contentFileFullName[wcslen(contentFileFullName)-1] == '\n'){
        contentFileFullName[wcslen(contentFileFullName)-1] = '\0';
    }
    fileContent(contentFileFullName);

}

void fileContent(wchar_t* absolutePath){
    wStringInQuatationMarks(absolutePath);
    forkk(L"contentCL.exe",absolutePath, INVALID_HANDLE_VALUE);

}

void calc(){
    forkk(L"VBCalculator.exe",L"", INVALID_HANDLE_VALUE);

}

void editor(){
    forkk(L"TextEditor.exe",L"", INVALID_HANDLE_VALUE);

}

void grep(){
    forkk(L"grepCL.exe",L"", INVALID_HANDLE_VALUE);

}


void mergeFiles(){
    forkk(L"mergeCL.exe",L"", INVALID_HANDLE_VALUE);

}

void mergePartOfFiles(){
    forkk(L"mergePCL.exe",L"", INVALID_HANDLE_VALUE);

}

void filesDiferences(){
    forkk(L"diffCL.exe",L"", INVALID_HANDLE_VALUE);

}

void find(wchar_t* path)
{
    wchar_t searchString[MAX_PATH];
    wchar_t directoryPath[MAX_PATH];

    printf("Search-String:");
    fgetws(searchString,MAX_PATH,stdin);
    if(searchString[wcslen(searchString)-1] == '\n'){
        searchString[wcslen(searchString)-1] = '\0';

    }

    if(wStringCheck(searchString) == 1){
        printf("\n");
        return;
    }

    printf("Directory:");
    fgetws(directoryPath,MAX_PATH,stdin);
    if(directoryPath[wcslen(directoryPath)-1] == '\n'){
        directoryPath[wcslen(directoryPath)-1] = '\0';

    }

    if(wStringCheck(directoryPath) == 1){
        printf("\n");
        return;
    }

    wchar_t* directoryAbsolutePath;
    if((directoryAbsolutePath = preparePathDependingOnType(path, directoryPath)) == NULL){
        return;

    }

    if(wcslen(directoryAbsolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(directoryAbsolutePath,L"")) == 3){
        printf("Invalid argument!\n\n");
        return;

    }

    if(existCheck == 1){
        printf("The argument must be a directory!\n\n");
        return;

    }

    if(existCheck == 0){
        printf("The argument doesn't exist as file!\n\n");
        return;

    }

    printf("\n");
    parse(directoryAbsolutePath, L"find", searchString, INVALID_HANDLE_VALUE);
}

void help(){
    printf("\n");
    forkk(L"contentCL.exe",L"\"Manual.txt\"", INVALID_HANDLE_VALUE);

}

void parse(wchar_t* path, PWCHAR control, wchar_t* parameter, HANDLE outputFileHandler){
    unsigned short parameterLength = 0;
    
    if(parameter){
        parameterLength = wcslen(parameter); 
    }

    wchar_t args[11+wcslen(path)-1+wcslen(control)+parameterLength+1];
    args[0] = '\0';
    wcscat_s(args,sizeof(args),L"\"");
    wcscat_s(args,sizeof(args),path);
    if(args[wcslen(args) - 1] == '\\')
    {
        args[wcslen(args) - 1] = '\0';    
    }
    wcscat_s(args,sizeof(args),L"\"");
    wcscat_s(args,sizeof(args),L" ");
    wcscat_s(args,sizeof(args),L"\"");
    wcscat_s(args, sizeof(args), control);
    wcscat_s(args,sizeof(args),L"\"");

    if(parameter)
    {
        wcscat_s(args,sizeof(args),L" \"");
        wcscat_s(args, sizeof(args), parameter);
        wcscat_s(args,sizeof(args),L"\"");
    }
    forkk(L"parseCL.exe",args, outputFileHandler);
}