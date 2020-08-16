#include "mados.h"
#define CMD L"C:\\Windows\\System32\\cmd.exe"

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

void wStringInQuatationMarks(wchar_t* string){
    wchar_t newString[wcslen(string)+3];
    newString[0] = '\0';
    wcscat(newString,L"\"");
    wcscat(newString,string);
    wcscat(newString,L"\"");
    wcscpy(string,newString);

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

void forkk(wchar_t *application,wchar_t *args){
    STARTUPINFOW s;
    PROCESS_INFORMATION p;
    ZeroMemory(&s,sizeof(STARTUPINFOW));
    s.cb = sizeof(STARTUPINFOW);
    ZeroMemory(&p,sizeof(PROCESS_INFORMATION));
    wchar_t commandLine[PATH];
    commandLine[0] = '\0';
    wcscat(commandLine,L"\"");
    wcscat(commandLine,application);
    wcscat(commandLine,L"\"");
    wcscat(commandLine,L" ");
    wcscat(commandLine,args);
    BOOL createProccesCheck = FALSE;
    SetConsoleCtrlHandler(NULL,FALSE);
createProccesCheck = CreateProcessW(
application,
commandLine,
NULL,
NULL,
FALSE,
0,
NULL,
NULL,
&s,
&p
    );
    SetConsoleCtrlHandler(NULL,TRUE);
    DWORD error = 0;
    if(createProccesCheck == FALSE){
        error = GetLastError();
        printf("ForkkCreateProcessError:%lu\n",error);
        ExitProcess(error);

    }

    if ((wcscmp(application,L"VBCalculator.exe") != 0) && (wcscmp(application,L"TextEditor.exe") != 0))
    if(WaitForSingleObject(p.hProcess,INFINITE) == WAIT_FAILED){
        error = GetLastError();
        printf("ForkkWaitForSingleObjectError:%lu\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(p.hProcess) == FALSE){
        error = GetLastError();
        printf("ForkkCloseHandleHProcessError:%lu\n",error);
        return;

    }

    if(CloseHandle(p.hThread) == FALSE){
        error = GetLastError();
        printf("ForkkCloseHandleHThreadError:%lu\n",error);
        return;

    }

}

void newPath(wchar_t *oldPath){
    wchar_t newPath[MAX_PATH];
    fgetws(newPath,MAX_PATH,stdin);
    if(newPath[wcslen(newPath)-1] == '\n'){
        newPath[wcslen(newPath)-1] = '\0';
    }

    if(wStringCheck(newPath) == 1){
        return;

    }

    if(pathType(newPath) == 1){
        printf("You need a absolute path!\n");
        return;

    }

    if(wcslen(newPath) > 247){
        printf("File name is too long!\n");
        return;

    }

    int pathCheck = 0;
    if((pathCheck=wExist(newPath,L"")) == 0){
        printf("This path doesn't exist as file!\n");
        return;

    }

    if(pathCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(pathCheck != 2){
        printf("This path isn't a directory!\n");
        return;

    }

    if(wcslen(newPath) == 3){

    }else{
        wcscat(newPath,L"\\");

    }

    wcscpy(oldPath,newPath);

}

void changePath(wchar_t *path){
    wchar_t relativeChangePath[MAX_PATH];
    fgetws(relativeChangePath,MAX_PATH,stdin);
    if(relativeChangePath[wcslen(relativeChangePath)-1] == '\n'){
        relativeChangePath[wcslen(relativeChangePath)-1] = '\0';
    }

    if(wStringCheck(relativeChangePath) == 1){
        return;

    }

    if(pathType(relativeChangePath) == 0){
        printf("You need a relative path!\n");
        return;

    }

    if((wcslen(path)+wcslen(relativeChangePath)) > 247){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(path,relativeChangePath)) == 0){
        printf("This path doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck != 2){
        printf("This path isn't a directory!\n");
        return;

    }


    wcscat(path,relativeChangePath);
    wcscat(path,L"\\");


}

void parse(wchar_t* path,wchar_t control){
    wchar_t args[8+wcslen(path)+1];
    args[0] = '\0';
    wcscat(args,L"\"");
    wcscat(args,path);
    wcscat(args,L"\\");
    if(control == 'R'){
        wcscat(args,L"\\");

    }
    wcscat(args,L"\"");
    wcscat(args,L" ");
    wcscat(args,L"\"");
    wcsncat(args,&control,1);
    wcscat(args,L"\"");
    forkk(L"parseCL.exe",args);

}

void createDirectoryWraper(wchar_t* path){
    wchar_t directoryShortPath[PATH];
    fgetws(directoryShortPath,PATH,stdin);
    if(directoryShortPath[wcslen(directoryShortPath)-1] == '\n'){
        directoryShortPath[wcslen(directoryShortPath)-1] = '\0';
    }

    if(wStringCheck(directoryShortPath) == 1){
        return;

    }

    if(pathType(directoryShortPath) == 0){
        printf("You need a relative path!\n");
        return;

    }

    wchar_t fullPath[wcslen(path)+wcslen(directoryShortPath)+1];
    fullPath[0] = '\0';
    wcscat(fullPath,path);
    wcscat(fullPath,directoryShortPath);

    createDirectory(fullPath);

}


void createDirectory(wchar_t* absolutePath){
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return;

    }

    DWORD error = 0;
    if(CreateDirectoryW(absolutePath,NULL) == 0){
        error = GetLastError();
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return;

        }

        if(error == ERROR_ALREADY_EXISTS){
            printf("The file already exists!\n");
            return;

        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return;

        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Permission denied!\n");
            return;

        }

        if(error == ERROR_FILENAME_EXCED_RANGE){
            printf("File name is too long!\n");
            return;

        }

        printf("CreateDirectoryCreateDirectoryError:%lu\n",error);
        return;

    }



}


void removeDirectoryWraper(wchar_t* path){
    wchar_t directoryShortPath[MAX_PATH];
    fgetws(directoryShortPath,MAX_PATH,stdin);
    if(directoryShortPath[wcslen(directoryShortPath)-1] == '\n'){
        directoryShortPath[wcslen(directoryShortPath)-1] = '\0';
    }

     if(wStringCheck(directoryShortPath) == 1){
            return;

    }

    if(pathType(directoryShortPath) == 0){
        printf("You need a relative path!\n");
        return;

    }

    wchar_t fullPath[wcslen(path)+wcslen(directoryShortPath)+1];
    fullPath[0] = '\0';
    wcscat(fullPath,path);
    wcscat(fullPath,directoryShortPath);

    removeDirectory(fullPath);

}

int removeDirectory(wchar_t* absolutePath){
    DWORD error = 0;
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return -1;

    }

    if(RemoveDirectoryW(absolutePath) == 0){
        error = GetLastError();

        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return error ;

        }

        if(error == ERROR_DIR_NOT_EMPTY){
            printf("The directory is not empty!\n");
            return error ;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("This path doesn't exist as file!\n");
            return error;
        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return error;

        }

        if(error == ERROR_DIRECTORY){
            printf("The arguments is a regular file, not a directory!\n");
            return error;

        }

        if(error == ERROR_FILENAME_EXCED_RANGE){
            printf("File name is too long!\n");
            return error;

        }

        printf("RemoveDirectoryRemoveDirectoryError:%lu\n",error);
        return error;

    }

    return 0;
}

void removeDirectoryRecursiveWraper(wchar_t* path){
    wchar_t name[MAX_PATH];
    fgetws(name,MAX_PATH,stdin);
    if(name[wcslen(name)-1] == '\n'){
        name[wcslen(name)-1] = '\0';
    }

    if(wStringCheck(name) == 1){
        return;

    }

    if(pathType(name) == 0){
        printf("You need a relative path!\n");
        return;

    }

    wchar_t removeDirectoryName[wcslen(path)+wcslen(name)+1];
    removeDirectoryName[0] = '\0';
    wcscat(removeDirectoryName,path);
    wcscat(removeDirectoryName,name);

    removeDirectoryRecursive(removeDirectoryName);

}

void removeDirectoryRecursive(wchar_t* absolutePath){
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return;

    }

    int pathCheck = 0;
    if((pathCheck=wExist(absolutePath,L"")) == 0){
        printf("This path doesn't exist as file!\n");
        return;

    }

    if(pathCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(pathCheck != 2){
        printf("This path isn't a directory!\n");
        return;

    }


    printf("\nList of deleted files:\n");
    parse(absolutePath,'R');
    printf("\n");
    if(removeDirectory(absolutePath) == 0){
        printf("The source directory was deleted successfully!\n");

    }

}

void createFileWraper(wchar_t* path){
    wchar_t name[MAX_PATH];
    fgetws(name,MAX_PATH,stdin);
    if(name[wcslen(name)-1] == '\n'){
        name[wcslen(name)-1] = '\0';

    }

    if(wStringCheck(name) == 1){
        return;

    }

    if(pathType(name) == 0){
        printf("You need a relative path!\n");
        return;

    }

    wchar_t fullPath[wcslen(path)+wcslen(name)+1+10];
    fullPath[0] = '\0';
    wcscat(fullPath,path);
    wcscat(fullPath,name);

    createFile(fullPath);

}

void createFile(wchar_t* absolutePath){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    DWORD error = 0;
    HANDLE createFileHandler = NULL;
    if((createFileHandler = CreateFileW(absolutePath,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument or file name is too long!\n");
            return;

        }

        if(error == 80){
            printf("The file exists.\n");
            return;

        }
        if(error == 3){
            printf("A component from argument doesn't exist or file name is too long!\n");
            return;

        }
        if(error == 5){
            printf("Path is a directory or access is denied!\n");
            return;
        }
        printf("CreateFileCreateFileAError:%lu\n",error);
        return;

    }

    if(CloseHandle(createFileHandler) == FALSE){
        error = GetLastError();
        printf("CreateFileCloseHandleError%lu\n",error);
        return;

    }

}

void removeFileWraper(wchar_t* path){
    wchar_t name[MAX_PATH];
    fgetws(name,MAX_PATH,stdin);
    if(name[wcslen(name)-1] == '\n'){
        name[wcslen(name)-1] = '\0';

    }

    if(wStringCheck(name) == 1){
        return;

    }

    if(pathType(name) == 0){
        printf("You need a relative path!\n");
        return;

    }

    wchar_t fullPath[wcslen(path)+wcslen(name)+1];
    fullPath[0] = '\0';
    wcscat(fullPath,path);
    wcscat(fullPath,name);

    removeFile(fullPath);

}

void removeFile(wchar_t* absolutePath){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

   }

    DWORD error = 0;
    if(DeleteFileW(absolutePath) == 0){
        error = GetLastError();

        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("This path doesn't exist as file!\n");
            return;
        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return;
        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Path is a directory or access is denied!\n");
            return;
        }

        printf("RemoveFileDeleteFileError:%lu\n",error);
        return;

    }

}

void renameFileWraper(){
    wchar_t oldName[MAX_PATH];
    printf("OldName:");
    fgetws(oldName,MAX_PATH,stdin);
    if(oldName[wcslen(oldName)-1] == '\n'){
        oldName[wcslen(oldName)-1] = '\0';

    }

    if(wStringCheck(oldName) == 1){
        return;

    }

    if(pathType(oldName) == 1){
        printf("You need a absolute path!\n");
        return;

    }

    if(wcslen(oldName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(oldName,L"")) == 0){
        printf("OldName doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    wchar_t newName[PATH];
    printf("NewName:");
    fgetws(newName,MAX_PATH,stdin);
    if(newName[wcslen(newName)-1] == '\n'){
        newName[wcslen(newName)-1] = '\0';

    }

    if(wStringCheck(newName) == 1){
        return;
    }

    if(pathType(newName) == 1){
        printf("You need a absolute path!\n");
        return;

    }


    if(wcslen(newName) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    existCheck = wExist(newName,L"");
    if(existCheck == 1 || existCheck == 2){
        printf("The NewName already exists!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    renameFile(oldName,newName);
    return;

}

void renameFile(wchar_t* oldName,wchar_t* newName){
    DWORD error = 0;
    if(MoveFileW(oldName,newName) == 0){
        error = GetLastError();

        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return;

        }

        if(error == ERROR_INVALID_PARAMETER){
            printf("Invalid parameter!\n");
            return;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("OldName doesn't exist as file!\n");
            return;

        }

        if(error == ERROR_ALREADY_EXISTS){
            printf("The NewName already exists!\n");
            return;

        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return;
        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Access is denied!\n");
            return;
        }

        if(error == ERROR_SHARING_VIOLATION){
            printf("The process cannot access the file because it is being used by another process!\n");
            return;
        }

        printf("renameFileMoveFileError:%lu\n",error);
        return;

    }

}

void start1(){
    wchar_t program[MAX_PATH];
    printf("Program:");
    fgetws(program,MAX_PATH,stdin);
    if(program[wcslen(program)-1] == '\n'){
        program[wcslen(program)-1] = '\0';

    }

    if(wStringCheck(program) == 1){
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(program,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck != 0){
        printf("First argument is a file(regular file or directory)!\n");
        return;

    }

    HINSTANCE shellCheck = 0;
    if((shellCheck=ShellExecuteW(NULL,L"open",program,NULL,NULL,1)) <= (HINSTANCE)32){
        if(shellCheck == (HINSTANCE)2){
            printf("Program not found!\n");
            return;

        }

        printf("Start1ShellExecuteError:%p!\n",shellCheck);
        return;

        }

}

void start2(wchar_t* path){
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    wchar_t program[MAX_PATH];
    printf("Program:");
    fgetws(program,MAX_PATH,stdin);
    if(program[wcslen(program)-1] == '\n'){
        program[wcslen(program)-1] = '\0';

    }


    if(wStringCheck(program) == 1){
        return;

    }

    if(wcslen(program) >= MAX_PATH -1){
        printf("Program name is too long!\n");
        return;
    }

    if(pathType(program) == 0){
        printf("You need a relative path!\n");
        return;

    }

    int exeCheck = 0;
    int existCheck = 0;
    if((existCheck=wExist(path,program)) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 1){
        if(wcscmp(program+wcslen(program)-4,L".exe") == 0){
            exeCheck =1 ;

        }else{

            printf("First argument is a non-executable file!\n");
            return;

        }

    }

    wchar_t* args;

    if(exeCheck == 0){
        if((args = (wchar_t*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,1+wcslen(path)+wcslen(program)+2)) == NULL){
            printf("Start2HeapAllocError!\n");
            return;

        }
        args[0] = '\0';
        wcscat(args,L"\"");
        wcscat(args,path);

        wchar_t openFileRelativeName[MAX_PATH];
        printf("FileName:");
        fgetws(openFileRelativeName,MAX_PATH,stdin);
        if(openFileRelativeName[wcslen(openFileRelativeName)-1] == '\n'){
            openFileRelativeName[wcslen(openFileRelativeName)-1] = '\0';

        }

        if(wStringCheck(openFileRelativeName) == 1){
            return;

        }

        if(pathType(openFileRelativeName) == 0){
            printf("You need a relative path!\n");
            return;

        }

        wcscat(args,openFileRelativeName);
        wcscat(args,L"\"");

        if(wcslen(args) >= MAX_PATH -3){
            printf("File name is too long!\n");
            return;
        }


        int existCheck = 0;
        if((existCheck=wExist(path,openFileRelativeName)) == 3){
            printf("Invalid argument!\n");
            return;

        }

        if(existCheck == 0){
            printf("Second argument doesn't exist as file!\n");
            return;

        }

        if(existCheck != 1){
            printf("Second argument isn't a regular file!\n");
            return;

        }

        HINSTANCE shellCheck = 0;
        if((shellCheck=ShellExecuteW(NULL,L"open",program,args,NULL,1)) <= (HINSTANCE)32){
            if(shellCheck == (HINSTANCE)2){
                printf("Program not found!\n");
                if(heapFreeChecker(processHeap,0,args) == FALSE){
                    return;

                }

                return;

            }
            printf("Start2ShellExecuteError:%p!\n",shellCheck);
            return;

        }


    }else{
        wchar_t list[THIRTY];wchar_t executable[1+wcslen(path)+wcslen(program)];
        printf("List of arguments:");_getws(list);
        if((args = HeapAlloc(processHeap,HEAP_ZERO_MEMORY,1+wcslen(list))) == NULL){
            printf("Start2HeapReAllocError!\n");
            return;

        }
        args[0] = '\0';
        wcscat(args,list);
        executable[0] = '\0';
        wcscat(executable,path);
        wcscat(executable,program);
        forkk(executable,args);


    }

    if(heapFreeChecker(processHeap,0,args) == FALSE){
        return;

    }

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

void back(wchar_t* path){
    if(wNumberOfAparition(path,'\\') < 2){
        return;

    }

    path[wcslen(path)-1] = '\0';
    int index = 0;
    if((index = wLastAparition(path,'\\')) < 0){
        printf("BackLastAparitionError:Error\n");
        ExitProcess(-1);

    }
    path[index+1] = '\0';

}

void cline(){
    if((ShellExecuteW(NULL,L"open",L"MAD OS Command Line.exe",NULL,NULL,1)) <= (HINSTANCE)32){
        printf("ClineShellExecuteError:Error!\n");
        return;

    }

}

void clearr(){
    COORD point = { 0, 0};
    HANDLE console;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    DWORD error;

    if((console=GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("ClearrGetStdHandleError:%lu\n",error);
        ExitProcess(error);

    }

    if(GetConsoleScreenBufferInfo(console,&screen) == 0){
        error = GetLastError();
        printf("ClearrGetConsoleScreenBufferError:%lu\n",error);
        ExitProcess(error);

    }

    if(FillConsoleOutputCharacterA(
    console,' ',screen.dwSize.X * screen.dwSize.Y,point,&written) == 0){
        error = GetLastError();
        printf("ClearrFillConsoleOutputCharacterAError:%lu\n",error);
        ExitProcess(error);

    }

    if(FillConsoleOutputAttribute(
    console,0,screen.dwSize.X * screen.dwSize.Y,point,&written) == 0){
        error = GetLastError();
        printf("ClearrFillConsoleOutputAttributeError:%lu\n",error);
        ExitProcess(error);

    }

    if(SetConsoleCursorPosition(console,point) == 0){
        error = GetLastError();
        printf("ClearrSetConsoleCursorPositionError:%lu\n",error);
        ExitProcess(error);

    }

}

void newCline(){
    if((ShellExecuteW(NULL,L"open",L"MAD OS Command Line.exe",NULL,NULL,1)) <= (HINSTANCE)32){
        printf("Error!\n");
        return;

    }

    ExitProcess(0);
}

void ipc(){
    forkk(CMD,L"/c ipconfig");

}

void ipca(){
    forkk(CMD,L"/c ipconfig /all");

}

void openPathWraper(){
    wchar_t openFileAbsoluteName[MAX_PATH];
    fgetws(openFileAbsoluteName,MAX_PATH,stdin);
    if(openFileAbsoluteName[wcslen(openFileAbsoluteName)-1] == '\n'){
        openFileAbsoluteName[wcslen(openFileAbsoluteName)-1] = '\0';

    }

    openPath(openFileAbsoluteName);

}

void openPath(wchar_t *absolutePath){
    if(wStringCheck(absolutePath) == 1){
        return;

    }

    if(pathType(absolutePath) == 1){
        printf("You need a absolute path!\n");
        return;

    }

    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

   }

    int existCheck = 0;
    if((existCheck=wExist(absolutePath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 0){
        printf("This path doesn't exist as file!\n");
        return;

    }

    HINSTANCE shellCheck = 0;
    if((shellCheck = ShellExecuteW(NULL,L"open",absolutePath,NULL,NULL,1)) <= (HINSTANCE)32){
        if(shellCheck == (HINSTANCE)5){
            printf("The operating system denied access to the specified file!\n");
            return;

        }

        printf("OpenPathShellExecuteError:%p!\n",shellCheck);
        return;

    }

}

void sort(){
    forkk(L"sortDirCL.exe",L"");

}

void help(){
    printf("\n");
    forkk(L"contentCL.exe",L"Manual.txt");

}


void copyFile(wchar_t* sourceAbsolutePath,wchar_t* destinationAbsolutePath){
    DWORD error = 0;
    if(CopyFileW(sourceAbsolutePath,destinationAbsolutePath,TRUE) == FALSE){
        error = GetLastError();
        if(error == 3){
            printf("DestinationPath doesn't exist!\n");
            return;

        }
        if(error == 80){
            printf("The file exists.\n\n");
            return;

        }

        printf("CopyFileCheck:%lu\n",error);
        return;

    }
    printf("Regular file was copied successfully!\n\n");

}

void myCopyFile(char* control){
    if(strcmp(control,"copy") == 0)
    forkk(L"copyCL.exe",L"");

    if(strcmp(control,"cut") == 0)
    forkk(L"cutCL.exe",L"");

}

void generateFile(){
    forkk(L"fileGeneratorCL.exe",L"");

}

void connectToURLWraper(){
    wchar_t domainName[MAX_PATH];
    printf("URL:");
    fgetws(domainName,MAX_PATH,stdin);
    if(domainName[wcslen(domainName)-1] == '\n'){
        domainName[wcslen(domainName)-1] = '\0';

    }

    wchar_t command[9+wcslen(domainName)];
    command[0] = '\0';
    wcscat(command,L"https://");
    wcscat(command,domainName);

    connectToURL(command);

}

void connectToURL(wchar_t* url){
    HINSTANCE shellCheck = 0;
    if((shellCheck = ShellExecuteW(NULL,L"open",url,NULL,NULL,3)) <= (HINSTANCE)32){
        printf("ConnectToURLShellExecuteError:%p!\n",shellCheck);
        return;

    }

    printf("Connected with success!\n");

}

void displayTime(){
    time_t t = 0;
    if((t = time(NULL)) == ((time_t)-1)){
        printf("Time error1!\n");
        return;

    }

    char* date;
    if((date = ctime(&t)) == NULL){
            printf("Time error!\n");
            return;

    }
    date[strlen(date) - 1] = '\0';

    if((date = ctime(&t)) == NULL){
        printf("Time error2!\n");
        return;

    }

    printf("%s\n",date);

}

void copyDirectoryWraper(char* control){
    wchar_t sourcePath[MAX_PATH];
    printf("SourceDirectory:");
    fgetws(sourcePath,MAX_PATH,stdin);
    if(sourcePath[wcslen(sourcePath)-1] == '\n'){
        sourcePath[wcslen(sourcePath)-1] = '\0';

    }

    if(wStringCheck(sourcePath) == 1){
        return;

    }

    if(pathType(sourcePath) == 1){
        printf("You need a absolute path!\n");
        return;

    }

    if(wcslen(sourcePath) > 247){
        printf("File name is too long!\n");
        return;

   }

    int existCheck = 0;
    if((existCheck=wExist(sourcePath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 0){
        printf("SourcePath doesn't exist as file!\n");
        return;

    }

    if(existCheck != 2){
        printf("SourcePath isn't a directory!\n");
        return;

    }

    wchar_t destinationPath[MAX_PATH];
    printf("DestinationDirectory:");

    fgetws(destinationPath,MAX_PATH,stdin);
    if(destinationPath[wcslen(destinationPath)-1] == '\n'){
        destinationPath[wcslen(destinationPath)-1] = '\0';

    }

    if(wStringCheck(destinationPath) == 1){
        return;

    }

    if(pathType(destinationPath) == 1){
        printf("You need a absolute path!\n\n");
        return;

    }

    if(wcslen(destinationPath) > 247){
        printf("File name is too long!\n\n");
        return;

   }

    if((existCheck=wExist(destinationPath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck != 0){
        printf("The file already exists!\n");
        return;

    }

    copyDirectory(sourcePath,destinationPath);

    if(strcmp(control,"cut") == 0){
        removeDirectoryRecursive(sourcePath);

    }


}

void copyDirectory(wchar_t* sourcePath,wchar_t* destinationPath){
    wchar_t command[52+wcslen(sourcePath)+wcslen(destinationPath)];
    command[0] = '\0';
    wcscat(command,L"/c ");
    wcscat(command,L"xcopy ");
    wcscat(command,L"\"");
    wcscat(command,sourcePath);
    wcscat(command,L"\" ");
    wcscat(command,L"\"");
    wcscat(command,destinationPath);
    wcscat(command,L"\" ");
    wcscat(command,L"/s ");
    wcscat(command,L"/e");
    forkk(CMD,command);

}

void backupWraper(wchar_t* path){
    wchar_t backUpFileRelativeName[MAX_PATH];
    printf("File to backup:");
    fgetws(backUpFileRelativeName,MAX_PATH,stdin);
    if(backUpFileRelativeName[wcslen(backUpFileRelativeName)-1] == '\n'){
        backUpFileRelativeName[wcslen(backUpFileRelativeName)-1] = '\0';

    }

    if(wStringCheck(backUpFileRelativeName) == 1){
        return;

    }

    if(pathType(backUpFileRelativeName) == 0){
        printf("You need a relative path!\n\n");
        return;

    }

    wchar_t fullPath[PATH];
    fullPath[0] = '\0';
    wcscat(fullPath,path);
    wcscat(fullPath,backUpFileRelativeName);

    backup(fullPath,backUpFileRelativeName);

}

void backup(wchar_t* absolutePath,wchar_t* name){
    if(wcslen(absolutePath) >= MAX_PATH - 1){
        printf("File name is too long!\n\n");
        return;

   }

    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(absolutePath,L"")) == 0){
        printf("SourcePath doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    wchar_t backupPath[OH];
    backupPath[0] = '\0';

    LPCWSTR variableName = L"USERPROFILE";
    LPWSTR variableValue;
    if((variableValue = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,PATH)) == NULL){
        printf("BckpHeapAllocError!\n");
        return;

    }
    DWORD size = PATH;

    GetEnvironmentVariableW(variableName,variableValue,size);
    wcscat(backupPath,variableValue);
    printf("BACKUP:");
    wcscat(backupPath,L"\\BACKUP");
    createDirectory(backupPath);

    wcscat(backupPath,L"\\");
    wcscat(backupPath,name);

    if(wExist(backupPath,L"") != 0){
        printf("Backup file exists.\n\n");
        return;

    }

    if(existCheck == 1){
        copyFile(absolutePath,backupPath);
        return;

    }

    if(existCheck == 2){
        wcscat(backupPath,L"\\");
        copyDirectory(absolutePath,backupPath);
        return;

    }

    if(heapFreeChecker(processHeap,0,variableValue) == FALSE){
        return;

    }

}

void fileContentWraper(){
    wchar_t path[PATH];
    printf("File-Path:");_getws(path);
    if(wStringCheck(path) == 1){
        return;

    }

    printf("\n");
    fileContent(path);

}


void fileContent(wchar_t* absolutePath){
    wStringInQuatationMarks(absolutePath);
    forkk(L"contentCL.exe",absolutePath);

}

void calc(){
    forkk(L"VBCalculator.exe",L"");

}

void netshProfiles(){
    forkk(CMD,L"/c netsh wlan show profiles");

}

void netshPasswordWraper(){
    wchar_t ssid[OH];
    printf("SSID:");_getws(ssid);

    if(wStringCheck(ssid) == 1){
        return;

    }

    netshPassword(ssid);

}

void netshPassword(wchar_t* ssid){
    wchar_t command[OH];
    command[0] = '\0';
    wcscat(command,L"/c netsh wlan show profile name=");
    wcscat(command,ssid);
    wcscat(command,L" ");
    wcscat(command,L"key=clear");
    forkk(CMD,command);

}

int characterCheck(char character){
    if(isdigit(character) == 0 && character != '-'  ){
        return 1;

    }

    return 0;

}

int spaceCountCheck(char* string){
    int nr = 0;

    for(int i = 0;i < strlen(string);i++){
        if(string[i] == 32){
            nr++;

        }

    }

    return nr;

}

int allDigits(char* string){
    if(characterCheck(string[0]) == 1){
        return 1;

    }

    for(int i = 1;i < strlen(string);i++){
        if(isdigit(string[i]) == 0){
            return 1;

        }
    }

    return 0;
}

int operatorCheck(char c){
    if (c != '+' && c != '-' && c != '*' && c != '/' && c != '%'){
        return 1;

    }

   return 0;

}

void eval(int operand1,int operation,int operand2){
    switch(operation){
    case '+' : printf("Result:%d\n\n",operand1 + operand2);break;
    case '-' : printf("Result:%d\n\n",operand1 - operand2);break;
    case '*' : printf("Result:%d\n\n",operand1 * operand2);break;
    case '/' : printf("Result:%.3f\n\n",((float)operand1 / (float)operand2));break;
    case '%' : printf("Result:%d\n\n",operand1 % operand2);break;

    }

    return;
}

char* breakString(char* string,char* separators){
    char* breakSt;
    int operand1,operand2;
    int operation;
    int stringLength = 0;
    char auxString[1];
    auxString[0] = '\0';
    strcat(auxString,string);

    if((breakSt = strtok(string,separators)) == NULL){
        return "NoMatch";

    }


    if(allDigits(breakSt) == 1){
        return "NoMatch";

    }

    if(auxString[strlen(breakSt)] != 32){
        return "NoMatch";

    }


    stringLength += strlen(breakSt);
    stringLength += 1;

    operand1 = atoi(breakSt);

    if((breakSt = strtok(NULL,separators)) == NULL){
        return "NoMatch";

    }


    if (strlen(breakSt) > 1){
        return "NoMatch";

    }

    if(operatorCheck(breakSt[0]) == 1){
        return "NoMatch";

    }

    stringLength += strlen(breakSt);
    stringLength += 1;


    if(auxString[stringLength -1] != 32){
        return "NoMatch";

    }

    operation = breakSt[0];

    if((breakSt = strtok(NULL,separators)) == NULL){
        return "NoMatch";

    }

    if(allDigits(breakSt) == 1){
        return "NoMatch";

    }

    operand2 = atoi(breakSt);

    if((breakSt = strtok(NULL,separators)) != NULL){
        return "NoMatch";

    }

    eval(operand1,operation,operand2);
    return "Match";

}


char* compute(char* expression){

    if(characterCheck(expression[0]) == 1){
        return "NoMatch";
    }

    if(spaceCountCheck(expression) > 2){
        return "NoMatch";
    }

    return breakString(expression," ");
}

void editor(){
    forkk(L"TextEditor.exe",L"");

}

void statusCheck(NET_API_STATUS status,LPDWORD error){
    if (status == ERROR_ACCESS_DENIED){
        printf("You don't have permission to do this operation.Please run this program as administrator!\n\n");
        return;

    }

    if(status == ERROR_INVALID_PASSWORD){
        printf("Incorrect Password!\n\n");
        return;

    }

    if(status == NERR_UserExists){
        printf("User exists!\n\n");
        return;

    }

    if(status == NERR_BadUsername){
        printf("Invalid user name!\n\n");
        return;

    }

    if(status == NERR_BadPassword){
        printf("Invalid password!\n\n");
        return;

    }

    if(status == NERR_UserNotFound){
        printf("User not found!\n\n");
        return;

    }

    if(status == NERR_GroupNotFound){
        printf("Local group not found!\n");
        return;

    }

    printf("StatusCheckError:%lu",status);
    if(error != NULL){
        printf("---Index:%lu\n\n",*error);

    }else{
        printf("\n\n");

    }

}

void getUserInfoWraper(){
    wchar_t userName[21];
    printf("Name:");
    fgetws(userName,21,stdin);
    if(wcslen(userName) < 20)
        userName[wcslen(userName)-1] = '\0';

    getUserInfo(userName);

}


void getUserInfo(wchar_t* userName){
    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }

    LPUSER_INFO_1 content = NULL;
    DWORD level= 1;
    NET_API_STATUS status = 0;

if((status = NetUserGetInfo(NULL,userName,level,(LPBYTE*)&content)) != NERR_Success){
    statusCheck(status,NULL);
    return;

}

wprintf(L"%ls;%ls;%ls\n\n",content->usri1_name,content->usri1_home_dir,content->usri1_comment);


}

void listUsers(){
    LPUSER_INFO_1 content = NULL;
    LPUSER_INFO_1 temporaryContent = NULL;
    DWORD level = 1;
    DWORD entries = 0;
    DWORD remainingEntries = 0;
    DWORD totalEntries =0;
    NET_API_STATUS status = 0;
    int i;

    printf("user_name;user_home_dir_path;user_comment\n");
do{
    status = NetUserEnum(NULL,level,0,(LPBYTE*)&content,MAX_PREFERRED_LENGTH,&entries,&remainingEntries,NULL);
        if((status == NERR_Success) || (status == ERROR_MORE_DATA)){
            if((temporaryContent = content) !=NULL){
                for(i = 0; i < entries; i++){
                    if(temporaryContent == NULL){
                        printf("An acces violation has occurred\n");
                        break;
                    }

                    wprintf(L"%ls;%ls;%ls\n",temporaryContent->usri1_name,temporaryContent->usri1_home_dir,temporaryContent->usri1_comment);
                    temporaryContent++;
                    totalEntries++;
                }

            }

        }else{
            statusCheck(status,NULL);

        }

        if (content != NULL){
            NetApiBufferFree(content);
            content = NULL;

        }
    }while(status == ERROR_MORE_DATA);

    if (content != NULL){
        NetApiBufferFree(content);

    }

    printf("Number of users:%lu\n\n",totalEntries);

}

void listUserLocalGroupsWraper(){
    wchar_t userName[21];
    printf("UserName:");
    fgetws(userName,21,stdin);
    if(wcslen(userName) < 20)
        userName[wcslen(userName)-1] = '\0';

    listUserLocalGroups(userName);


}

void listUserLocalGroups(wchar_t* userName){
    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }

    LPLOCALGROUP_USERS_INFO_0 content = NULL;
    LPLOCALGROUP_USERS_INFO_0 temporaryContent = NULL;
    DWORD level = 0;
    DWORD entries = 0;
    DWORD remainingEntries = 0;
    DWORD totalEntries =0;
    NET_API_STATUS status = 0;
    int i;

    printf("<GroupName>\n");
do{
    status = NetUserGetLocalGroups(NULL,userName,level,LG_INCLUDE_INDIRECT,(LPBYTE*)&content,MAX_PREFERRED_LENGTH,&entries,&remainingEntries);
        if((status == NERR_Success) || (status == ERROR_MORE_DATA)){
            if((temporaryContent = content) !=NULL){
                for(i = 0; i < entries; i++){
                    if(temporaryContent == NULL){
                        printf("An acces violation has occurred\n");
                        break;
                    }

                    wprintf(L"<%ls>\n",temporaryContent->lgrui0_name);
                    temporaryContent++;
                    totalEntries++;
                }

            }

        }else{
            statusCheck(status,NULL);

        }

        if (content != NULL){
            NetApiBufferFree(content);
            content = NULL;

        }
    }while(status == ERROR_MORE_DATA);

    if (content != NULL){
        NetApiBufferFree(content);

    }

    printf("Number of user local groups:%lu\n\n",totalEntries);

}

void addUserWraper(){
    wchar_t userName[21];
    userName[0] = '\0';
    printf("UserName:");
    fgetws(userName,21,stdin);
    if(userName[wcslen(userName)-1] == '\n'){
        userName[wcslen(userName)-1] = '\0';

    }

    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }


    fflush(stdin);

    wchar_t userPassword[21];
    userPassword[0] = '\0';
    printf("UserPassword:");
    fgetws(userPassword,LM20_PWLEN+1,stdin);
    if(userPassword[wcslen(userPassword)-1] == '\n'){
        userPassword[wcslen(userPassword)-1] = '\0';

    }

    addUser(userName,userPassword);

}

void addUser(wchar_t* userName,wchar_t* userPassword){
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    USER_INFO_1 content;
    LOCALGROUP_MEMBERS_INFO_3 account;

    DWORD level = 1;
    DWORD error = -1;

    if((content.usri1_name = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,100)) == NULL){
        printf("AddUserHeapAllocError!\n");
        return;

    }

    if((content.usri1_password = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,100)) == NULL){
        printf("AddUserHeapAllocError!\n");
        return;

    }

    wcscat(content.usri1_name,userName);
    wcscat(content.usri1_password,userPassword);

    content.usri1_priv = USER_PRIV_USER;
    content.usri1_home_dir = NULL;
    content.usri1_comment = NULL;
    content.usri1_flags = UF_SCRIPT | UF_NORMAL_ACCOUNT | UF_DONT_EXPIRE_PASSWD;
    content.usri1_script_path = NULL;

    NET_API_STATUS status = 0;
    status = NetUserAdd(NULL,level,(LPBYTE)&content,&error);

    if(status == NERR_Success){
        printf("A new user has been added succesfully!\n");

    }else{
        statusCheck(status,&error);

        if(heapFreeChecker(processHeap,0,content.usri1_name) == FALSE){
            return;

        }

        if(heapFreeChecker(processHeap,0,content.usri1_password) == FALSE){
            return;

        }

        return;

    }

    account.lgrmi3_domainandname = content.usri1_name;

    status = NetLocalGroupAddMembers(NULL,L"Users",3,(LPBYTE)&account,1);

    if(status == NERR_Success){
        printf("User has been added succesfully in \"Users\" group!");

    }else{
        statusCheck(status,NULL);

        if(heapFreeChecker(processHeap,0,content.usri1_name) == FALSE){
            return;

        }

        if(heapFreeChecker(processHeap,0,content.usri1_password) == FALSE){
            return;

        }

        return;

    }

    if(heapFreeChecker(processHeap,0,content.usri1_name) == FALSE){
        return;

    }

    if(heapFreeChecker(processHeap,0,content.usri1_password) == FALSE){
        return;

    }

    if(wcslen(userPassword) == 0){
        printf("\nAttention! The new password you introduced have length 0 => This account doesn't have a password!");

    }

    printf("\n\n");

}

void deleteUserWraper(){
    wchar_t userName[21];
    printf("Name:");
    fgetws(userName,21,stdin);
    if(userName[wcslen(userName)-1] == '\n')
        userName[wcslen(userName)-1] = '\0';


    deleteUser(userName);
}

void deleteUser(wchar_t *userName){
    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }


    LPCWSTR localComputer = NULL;
    NET_API_STATUS status = 0;

    status = NetUserDel(localComputer,userName);

    if(status == NERR_Success){
        printf("User has been deleted succesfully!\n\n");

    }else{
        statusCheck(status,NULL);
        return;

    }

}


void changeUserPasswordWraper(){
    wchar_t userName[21];userName[0] = '\0';
    wchar_t oldPassword[LM20_PWLEN+1];oldPassword[0] = '\0';
    wchar_t newPassword[LM20_PWLEN+1];newPassword[0] = '\0';

    printf("UserName:");
    fgetws(userName,21,stdin);
    if(userName[wcslen(userName)-1] == '\n'){
        userName[wcslen(userName)-1] = '\0';

    }

    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }

    fflush(stdin);
    printf("OldPassword:");
    fgetws(oldPassword,LM20_PWLEN+1,stdin);
    if(oldPassword[wcslen(oldPassword)-1] == '\n')
        oldPassword[wcslen(oldPassword)-1] = '\0';

    fflush(stdin);
    printf("NewPassword:");
    fgetws(newPassword,LM20_PWLEN+1,stdin);
    if(newPassword[wcslen(newPassword)-1] == '\n')
        newPassword[wcslen(newPassword)-1] = '\0';

    changeUserPassword(userName,oldPassword,newPassword);

}


void changeUserPassword(wchar_t* userName,wchar_t* userOldPassword,wchar_t* userNewPassword){
    LPCWSTR localComputer = NULL;
    NET_API_STATUS status = 0;

    status = NetUserChangePassword(localComputer,userName,userOldPassword,userNewPassword);

    if(status == NERR_Success){
        printf("Password has been updated succesfully!");

    }else{
        statusCheck(status,NULL);
        return;

    }

    if(wcscmp(userOldPassword,userNewPassword) == 0){
        printf("\nAttention! The new password you introduced are the same with the old password!");

    }

    if(wcslen(userNewPassword) == 0){
        printf("\nAttention! The new password you introduced have length 0 => This account doesn't have a password!");

    }

    printf("\n\n");
}

void getLocalGroupInfoWraper(){
    wchar_t groupName[21];
    printf("Group name:");
    fgetws(groupName,21,stdin);
    if(wcslen(groupName) < 20)
        groupName[wcslen(groupName)-1] = '\0';

    getLocalGroupInfo(groupName);

}


void getLocalGroupInfo(wchar_t* groupName){
    if(wStringCheck(groupName) == 1){
        printf("\n");
        return;

    }

    LPGROUP_INFO_1 content = NULL;
    DWORD level= 1;
    NET_API_STATUS status = 0;

if((status = NetLocalGroupGetInfo(NULL,groupName,level,(LPBYTE*)&content)) != NERR_Success){
    statusCheck(status,NULL);
    return;

}

wprintf(L"%ls;%ls\n\n",content->grpi1_name,content->grpi1_comment);


}


void listLocalGroups(){
    LPLOCALGROUP_INFO_1 content = NULL;
    LPLOCALGROUP_INFO_1 temporaryContent = NULL;
    DWORD level = 1;
    DWORD entries = 0;
    DWORD remainingEntries = 0;
    DWORD totalEntries =0;
    NET_API_STATUS status = 0;
    int i;

    printf("group_name;group_comment\n");
do{
    status = NetLocalGroupEnum(NULL,level,(LPBYTE*)&content,MAX_PREFERRED_LENGTH,&entries,&remainingEntries,NULL);
        if((status == NERR_Success) || (status == ERROR_MORE_DATA)){
            if((temporaryContent = content) !=NULL){
                for(i = 0; i < entries; i++){
                    if(temporaryContent == NULL){
                        printf("An acces violation has occurred\n");
                        break;
                    }

                    wprintf(L"%ls;%ls\n",temporaryContent->lgrpi1_name,temporaryContent->lgrpi1_comment);
                    temporaryContent++;
                    totalEntries++;
                }

            }

        }else{
            statusCheck(status,NULL);

        }

        if (content != NULL){
            NetApiBufferFree(content);
            content = NULL;

        }
    }while(status == ERROR_MORE_DATA);

    if (content != NULL){
        NetApiBufferFree(content);

    }

    printf("Number of local groups:%lu\n\n",totalEntries);

}


void listLocalGroupMembersWraper(){
    wchar_t localGroupName[21];
    printf("LocalGroupName:");
    fgetws(localGroupName,21,stdin);
    if(wcslen(localGroupName) < 20)
        localGroupName[wcslen(localGroupName)-1] = '\0';
    printf("\n");

    listLocalGroupMembers(localGroupName);

}

void listLocalGroupMembers(wchar_t* localGroupName){
    if(wStringCheck(localGroupName) == 1){
        return;

    }

    LPLOCALGROUP_MEMBERS_INFO_3 content = NULL;
    LPLOCALGROUP_MEMBERS_INFO_3 temporaryContent = NULL;
    DWORD level = 3;
    DWORD entries = 0;
    DWORD remainingEntries = 0;
    DWORD totalEntries =0;
    NET_API_STATUS status = 0;
    int i;

    printf("<DomainName>\\<AccountName>\n");
do{
    status = NetLocalGroupGetMembers(NULL,localGroupName,level,(LPBYTE*)&content,MAX_PREFERRED_LENGTH,&entries,&remainingEntries,NULL);
        if((status == NERR_Success) || (status == ERROR_MORE_DATA)){
            if((temporaryContent = content) !=NULL){
                for(i = 0; i < entries; i++){
                    if(temporaryContent == NULL){
                        printf("An acces violation has occurred\n");
                        break;
                    }

                    wprintf(L"%ls\n",temporaryContent->lgrmi3_domainandname);
                    temporaryContent++;
                    totalEntries++;
                }

            }

        }else{
            statusCheck(status,NULL);

        }

        if (content != NULL){
            NetApiBufferFree(content);
            content = NULL;

        }
    }while(status == ERROR_MORE_DATA);

    if (content != NULL){
        NetApiBufferFree(content);

    }

    printf("Number of local group members:%lu\n\n",totalEntries);

}

void EnumProcessesWraper(DWORD* processesList,DWORD* numberOfProcesses){
    DWORD returnBytes = 0;

    DWORD error = 0;
    if(EnumProcesses(processesList,2048,&returnBytes) == FALSE){
        error = GetLastError();
        printf("EnumProcessesError:%lu\n\n",error);
        ExitProcess(error);

    }
    (*numberOfProcesses) = returnBytes/sizeof(DWORD);

}

void listProcessesWraper(char* control){
    wchar_t processName[50];
    printf("Process name:");
    fgetws(processName,50,stdin);
    if(processName[wcslen(processName)-1] == '\n')
        processName[wcslen(processName)-1] = '\0';

    listProcesses(processName,control);

}

void listProcesses(wchar_t* pName,char* control){
    if(pName != NULL){
        if(wStringCheck(pName) == 1){
            return;

        }
    }

    printf("\nName\t\tPID\n");

    DWORD processesList[2048];
    DWORD numberOfProcesses = 0;
    int processCount = 0;
    DWORD error = 0;

    EnumProcessesWraper(processesList,&numberOfProcesses);


    wchar_t processName[OH] = L"Unkown";
    for(int i=0;i < numberOfProcesses;i++){
        if(processesList[i] == 0)
            continue;

        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,processesList[i]);
        if(processHandle == NULL){
            error = GetLastError();
            if(error == ERROR_ACCESS_DENIED){
                continue;

            }

            printf("ListProcessesOpenProcessError:%lu---PID:%lu\n",error,processesList[i]);
            continue;

        }

        if(processHandle != NULL){
            HMODULE firstModule;
            DWORD totalBytesNeededToStoreAllModules;
            if(EnumProcessModules(processHandle,&firstModule,sizeof(HMODULE),&totalBytesNeededToStoreAllModules) != FALSE ){
                if(GetModuleBaseNameW(processHandle,firstModule,processName,sizeof(processName)) == 0){
                   error = GetLastError();
                    printf("ListProcessesGetModuleBaseNameError:%lu---PID:%lu\n\n\n",error,processesList[i]);
                    continue;
                }

                if(pName != NULL){
                    if(wcscmp(pName,processName) == 0){
                       processCount++;
                       if(control == NULL){
                        wprintf(L"%s\t%lu\n",processName,processesList[i]);
                       }

                        if(control != NULL){
                            if(strcmp(control,"r") == 0){
                                if(wcscmp(pName,L"chrome.exe") == 0 && processCount > 1)
                                break;

                            wprintf(L"%s\t%lu--->Kill...\n",processName,processesList[i]);
                            killProcess(processesList[i]);

                            }

                        }

                    }

                }

            }else{
                    error = GetLastError();
                    printf("ListProcessesEnumProccesModules:%lu---PID:%lu\n\n\n",error,processesList[i]);
                    continue;
            }
        }
        if(pName == NULL){
            wprintf(L"%s\t%lu\n",processName,processesList[i]);
        }

            CloseHandle(processHandle);

    }

    if(pName != NULL){
        printf("\nProgram founds %d process with given name!\n\n",processCount);
    }

    printf("\n");
}

void killProcessWraper(){
    unsigned int killPid = -1;
    printf("PID:");scanf("%d",&killPid);
    killProcess(killPid);

}

void killProcess(DWORD killPid){
    if(killPid == GetCurrentProcessId()){
        printf("The specified PID is PID of current process!\n\n");
        return;
    }

    DWORD error = 0;
    HANDLE processHandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE,FALSE,killPid);
        if(processHandle == NULL){
            error = GetLastError();
            if(error == ERROR_ACCESS_DENIED){
                printf("Acces denied!\n\n");
                return;

            }

            if(error == ERROR_INVALID_PARAMETER){
                printf("There is not a process with this PID!\n\n");
                return ;

            }

            printf("KillProcessOpenProccesError:%lu---PID:%lu\n",error,killPid);
            return;

        }

    if(TerminateProcess(processHandle,-5) == 0){
        printf("TerminateProccesError:%lu---PID:%lu\n",error,killPid);
        return;

    }

    if(WaitForSingleObject(processHandle,INFINITE) == WAIT_FAILED){
        error = GetLastError();
        printf("WaitForSingleObjectCheck:%lu\n",error);
        return;

    }

    if(CloseHandle(processHandle) == FALSE){
        error = GetLastError();
        return;

    }

    printf("Process was killed succesfully!\n\n");
}

void changeColorWraper(wchar_t* control){
    wchar_t color[THIRTY];
    fgetws(color,THIRTY,stdin);
    if(color[wcslen(color)-1] == '\n'){
        color[wcslen(color)-1] = '\0';
    }

    changeColor(color,control);
}

void changeColor(wchar_t* color,wchar_t* control){
    if(wStringCheck(color) == 1){
        return;

    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE out;
    int c;

    DWORD error = 0;
    if((out = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    if(GetConsoleScreenBufferInfo(out,&csbi) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    int colorCheck=0;
    if(wcscmp(color,L"black") == 0){
        c = 0;
        colorCheck=1;

    }
    if(wcscmp(color,L"blue") == 0){
        c = 1;
        colorCheck=1;

    }
    if(wcscmp(color,L"green") == 0){
        c = 2;
        colorCheck=1;

    }
    if(wcscmp(color,L"aqua") == 0){
        c = 3;
        colorCheck=1;

    }
    if(wcscmp(color,L"red") == 0){
        c = 4;
        colorCheck=1;

    }
    if(wcscmp(color,L"purple") == 0){
        c = 5;
        colorCheck=1;

    }
    if(wcscmp(color,L"yellow") == 0){
        c = 6;
        colorCheck=1;

    }
    if(wcscmp(color,L"white") == 0){
        c = 7;
        colorCheck=1;

    }
    if(wcscmp(color,L"gray") == 0){
        c = 8;
        colorCheck=1;

    }
    if(wcscmp(color,L"lblue") == 0){
        c = 9;
        colorCheck=1;

    }
    if(wcscmp(color,L"lgreen") == 0){
        c = 10;
        colorCheck=1;

    }
    if(wcscmp(color,L"laqua") == 0){
        c = 11;
        colorCheck=1;

    }
    if(wcscmp(color,L"lred") == 0){
        c = 12;
        colorCheck=1;

    }
    if(wcscmp(color,L"lpurple") == 0){
        c = 13;
        colorCheck=1;

    }
    if(wcscmp(color,L"lyellow") == 0){
        c = 14;
        colorCheck=1;

    }
    if(wcscmp(color,L"bwhite") == 0){
        c = 15;
        colorCheck=1;

    }
    if(colorCheck == 0){
        printf("Invalid color!\n\n");
        return;

    }

    int attr = 0;
    attr = csbi.wAttributes;

    if(wcscmp(control,L"text") == 0){
        attr = attr & 240;
        attr = attr + c;

    }

    if(wcscmp(control,L"background") == 0){
        attr = attr & 15;
        attr = attr | (c << 4);

    }


    if(SetConsoleTextAttribute(out,attr) == 0){
        error  = GetLastError();
        printf("Error:%lu\n",error);

    }

}
