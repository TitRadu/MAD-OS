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
    wcscat_s(newString,sizeof(newString),L"\"");
    wcscat_s(newString,sizeof(newString),string);
    wcscat_s(newString,sizeof(newString),L"\"");
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

void forkk(wchar_t *application,wchar_t *args){
    STARTUPINFOW s;
    PROCESS_INFORMATION p;
    ZeroMemory(&s,sizeof(STARTUPINFOW));
    s.cb = sizeof(STARTUPINFOW);
    ZeroMemory(&p,sizeof(PROCESS_INFORMATION));
    wchar_t commandLine[PATH];
    commandLine[0] = '\0';
    wcscat_s(commandLine,sizeof(commandLine),L"\"");
    wcscat_s(commandLine,sizeof(commandLine),application);
    wcscat_s(commandLine,sizeof(commandLine),L"\"");
    wcscat_s(commandLine,sizeof(commandLine),L" ");
    wcscat_s(commandLine,sizeof(commandLine),args);

    wchar_t applicationCopy[MAX_PATH];
    wcscpy_s(applicationCopy,sizeof(applicationCopy),application);
    wchar_t* applicationDirectory = wStringWithoutLast(applicationCopy,'\\');

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
applicationDirectory,
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

void changePath(wchar_t *path){
    wchar_t changePath[MAX_PATH];
    fgetws(changePath,MAX_PATH,stdin);
    if(changePath[wcslen(changePath)-1] == '\n'){
        changePath[wcslen(changePath)-1] = '\0';
    }

    if(wStringCheck(changePath) == 1){
        return;

    }


    wchar_t absolutePath[MAX_PATH];

    if(pathType(changePath) == 0){
        wcscpy_s(absolutePath,sizeof(absolutePath),changePath);

    }else{
        wcscpy_s(absolutePath,sizeof(absolutePath),path);
        wcscat_s(absolutePath,sizeof(absolutePath),changePath);

    }

    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(absolutePath,L"")) == 0){
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


    wcscpy_s(path,MAX_PATH*sizeof(wchar_t),absolutePath);
    if(wcslen(path) != 3){
        wcscat_s(path,MAX_PATH*sizeof(wchar_t),L"\\");

    }

}

void parse(wchar_t* path,wchar_t control){
    wchar_t args[8+wcslen(path)+1];
    args[0] = '\0';
    wcscat_s(args,sizeof(args),L"\"");
    wcscat_s(args,sizeof(args),path);
    wcscat_s(args,sizeof(args),L"\\");
    if(control == 'R'){
        wcscat_s(args,sizeof(args),L"\\");

    }
    wcscat_s(args,sizeof(args),L"\"");
    wcscat_s(args,sizeof(args),L" ");
    wcscat_s(args,sizeof(args),L"\"");
    wcsncat(args,&control,1);
    wcscat_s(args,sizeof(args),L"\"");
    forkk(L"parseCL.exe",args);

}

wchar_t* preparePathDependingOnType(wchar_t* path,wchar_t* checkPath){
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return NULL;

    }

    wchar_t* absolutePath;
    if((absolutePath = (wchar_t*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(wchar_t)*MAX_PATH)) == NULL){
        printf("PreparePathDepedingOnTypeHeapAllocError!\n");
        return NULL;

    }

    if(pathType(checkPath) == ABSOLUTE_PATH){
        wcscpy_s(absolutePath,sizeof(wchar_t)*MAX_PATH,checkPath);

    }else{
        wcscpy_s(absolutePath,sizeof(wchar_t)*MAX_PATH,path);
        wcscat_s(absolutePath,sizeof(wchar_t)*MAX_PATH,checkPath);

    }

    return absolutePath;

}

void chooseFileOperation(wchar_t* absolutePath,char* control){
    if(strcmp(control,"cdir") == 0){
            createDirectory(absolutePath);
            return;

        }

    if(strcmp(control,"rdir") == 0){
            removeDirectory(absolutePath);
            return;

        }

    if(strcmp(control,"Rdir") == 0){
            removeDirectoryRecursive(absolutePath);
            return;

        }

    if(strcmp(control,"cfile") == 0){
            createFile(absolutePath);
            return;

        }

    if(strcmp(control,"rfile") == 0){
            removeFile(absolutePath);
            return;

        }

}

void fileOperationWraper(wchar_t* path, char* control){
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    wchar_t filePath[MAX_PATH];
    fgetws(filePath,MAX_PATH,stdin);
    if(filePath[wcslen(filePath)-1] == '\n'){
        filePath[wcslen(filePath)-1] = '\0';
    }

    if(wStringCheck(filePath) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,filePath)) == NULL){
        return;

    }

    chooseFileOperation(absolutePath,control);

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

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

void renameFileWraper(wchar_t* path){
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    wchar_t oldName[MAX_PATH];
    printf("OldName:");
    fgetws(oldName,MAX_PATH,stdin);
    if(oldName[wcslen(oldName)-1] == '\n'){
        oldName[wcslen(oldName)-1] = '\0';

    }

    if(wStringCheck(oldName) == 1){
        return;

    }

    wchar_t* absoluteOldPath;
    if((absoluteOldPath = preparePathDependingOnType(path,oldName)) == NULL){
        return;

    }

    if(wcslen(absoluteOldPath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(absoluteOldPath,L"")) == 0){
        printf("Old name doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    wchar_t newName[MAX_PATH];
    printf("NewName:");
    fgetws(newName,MAX_PATH,stdin);
    if(newName[wcslen(newName)-1] == '\n'){
        newName[wcslen(newName)-1] = '\0';

    }

    if(wStringCheck(newName) == 1){
        return;
    }

    wchar_t* absoluteNewPath;
    if((absoluteNewPath = preparePathDependingOnType(path,newName)) == NULL){
        return;

    }

    if(wcslen(absoluteNewPath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    existCheck = wExist(absoluteNewPath,L"");
    if(existCheck == 1 || existCheck == 2){
        printf("The new name already exists!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    renameFile(absoluteOldPath,absoluteNewPath);

    if(heapFreeChecker(processHeap,0,absoluteOldPath) == FALSE){
        return;

    }
    if(heapFreeChecker(processHeap,0,absoluteNewPath) == FALSE){
        return;

    }

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
            printf("Old name doesn't exist as file!\n");
            return;

        }

        if(error == ERROR_ALREADY_EXISTS){
            printf("The new name already exists!\n");
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

void openDefault(){
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

void openFileWithProgramWraper(wchar_t* path){
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

    int existCheck = 0;
    if((existCheck=wExist(path,program)) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 1 || existCheck == 2){
        printf("First argument is a file(regular file or directory)!\n");
        return;
    }

    wchar_t absolutePath[MAX_PATH];
    absolutePath[0] = '\0';
    wcscat_s(absolutePath,sizeof(absolutePath),path);

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

    wcscat_s(absolutePath,sizeof(absolutePath),openFileRelativeName);

    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;
    }

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

    openFileWithProgram(program,absolutePath);

}
void openFileWithProgram(wchar_t* program,wchar_t* absolutePath){
    HINSTANCE shellCheck = 0;
    if((shellCheck=ShellExecuteW(NULL,L"open",program,absolutePath,NULL,1)) <= (HINSTANCE)32){
        if(shellCheck == (HINSTANCE)2){
            printf("Program not found!\n");
            return;

        }
        printf("OpenFileWithProgramShellExecuteError:%p!\n",shellCheck);
        return;

    }


}

void run(){
    wchar_t executable[MAX_PATH];
    printf("Executable:");
    fgetws(executable,MAX_PATH,stdin);
    if(executable[wcslen(executable)-1] == '\n'){
        executable[wcslen(executable)-1] = '\0';

    }


    if(wStringCheck(executable) == 1){
        return;

    }

    if(wcslen(executable) >= MAX_PATH -1){
        printf("Executable name is too long!\n");
        return;
    }

    if(pathType(executable) == 1){
        printf("You need a absolute path!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(executable,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 2){
        printf("The argument is a directory!\n\n");
        return;

    }

    if(existCheck == 0){
        printf("The argument doesn't exist as file!\n\n");

    }

    if(existCheck == 1){
        if(wcscmp(executable+wcslen(executable)-4,L".exe") == 0){
            wchar_t list[THIRTY];
            printf("List of arguments:");_getws(list);
            forkk(executable,list);


        }else{

            printf("First argument is a non-executable file!\n\n");
            return;

        }

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
    if((ShellExecuteW(NULL,L"open",L"Command Line.exe",NULL,NULL,1)) <= (HINSTANCE)32){
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
    if((ShellExecuteW(NULL,L"open",L"Command Line.exe",NULL,NULL,1)) <= (HINSTANCE)32){
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
    forkk(L"contentCL.exe",L"\"Manual.txt\"");

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
    wcscat_s(command,sizeof(command),L"https://");
    wcscat_s(command,sizeof(command),domainName);

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
    sourcePath[wcslen(sourcePath) + 1] = '\0';
    destinationPath[wcslen(destinationPath) + 1] = '\0';

    SHFILEOPSTRUCTW s = {0};
    s.pFrom = sourcePath;
    s.pTo = destinationPath;
    s.wFunc = FO_COPY;

    int error = 0;
    if((error = SHFileOperationW(&s)) != 0){
        if(error == 2 || error == 124){
            printf("Source directory doesn't exist!\n\n");
            return;

        }
        if(error == 1223){
            printf("Operation was cancelled!\n\n");
            return;

        }

        printf("Error:%d\n",error);
        return;

    }

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

    wchar_t fullPath[MAX_PATH];
    fullPath[0] = '\0';
    wcscat_s(fullPath,sizeof(fullPath),path);
    wcscat_s(fullPath,sizeof(fullPath),backUpFileRelativeName);

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

    wchar_t backupPath[MAX_PATH];
    backupPath[0] = '\0';

    LPWSTR variableValue;
    if((variableValue = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(wchar_t)*MAX_PATH)) == NULL){
        printf("BckpHeapAllocError!\n");
        return;

    }

    GetEnvironmentVariableW(L"USERPROFILE",variableValue,sizeof(wchar_t)*MAX_PATH);
    wcscat_s(backupPath,sizeof(backupPath),variableValue);
    printf("BACKUP:");
    wcscat_s(backupPath,sizeof(backupPath),L"\\BACKUP");
    createDirectory(backupPath);

    wcscat_s(backupPath,sizeof(backupPath),L"\\");
    wcscat_s(backupPath,sizeof(backupPath),name);

    if(wExist(backupPath,L"") != 0){
        printf("Backup file exists.\n\n");
        return;

    }

    if(existCheck == 1){
        copyFile(absolutePath,backupPath);
        return;

    }

    if(existCheck == 2){
        copyDirectory(absolutePath,backupPath);
        return;

    }

    if(heapFreeChecker(processHeap,0,variableValue) == FALSE){
        return;

    }

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
    wcscat_s(command,sizeof(command),L"/c netsh wlan show profile name=");
    wcscat_s(command,sizeof(command),ssid);
    wcscat_s(command,sizeof(command),L" ");
    wcscat_s(command,sizeof(command),L"key=clear");
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
    wchar_t userName[22];
    printf("Name:");
    fgetws(userName,22,stdin);
    if(userName[wcslen(userName)-1] == '\n'){
        userName[wcslen(userName)-1] = '\0';

    }

    getUserInfo(userName);

}


void getUserInfo(wchar_t* userName){
    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }

    if(wcslen(userName) > 20){
        printf("User name is too long!\n\n");
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
    wchar_t userName[22];
    userName[0] = '\0';
    printf("UserName:");
    fgetws(userName,22,stdin);
    if(userName[wcslen(userName)-1] == '\n'){
        userName[wcslen(userName)-1] = '\0';

    }

    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }

    if(wcslen(userName) > 20){
        printf("User name is too long!\n\n");
        return;

    }

    fflush(stdin);

    wchar_t userPassword[LM20_PWLEN+2];
    userPassword[0] = '\0';
    printf("UserPassword:");
    fgetws(userPassword,LM20_PWLEN+2,stdin);
    if(userPassword[wcslen(userPassword)-1] == '\n'){
        userPassword[wcslen(userPassword)-1] = '\0';

    }

    if(wcslen(userPassword) > 14){
        printf("Password is too long!\n\n");
        return;

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

    if((content.usri1_name = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,22*sizeof(wchar_t))) == NULL){
        printf("AddUserHeapAllocError!\n");
        return;

    }

    if((content.usri1_password = (LPWSTR)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,(LM20_PWLEN+2)*sizeof(wchar_t))) == NULL){
        printf("AddUserHeapAllocError!\n");
        return;

    }
    wcscat_s(content.usri1_name,22*sizeof(wchar_t),userName);
    wcscat_s(content.usri1_password,(LM20_PWLEN+2)*sizeof(wchar_t),userPassword);

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
    wchar_t userName[22];
    printf("Name:");
    fgetws(userName,22,stdin);
    if(userName[wcslen(userName)-1] == '\n'){
        userName[wcslen(userName)-1] = '\0';

    }

    if(wcslen(userName) > 20){
        printf("User name is too long!\n\n");
        return;

    }

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
    wchar_t userName[22];userName[0] = '\0';
    wchar_t oldPassword[LM20_PWLEN+2];oldPassword[0] = '\0';
    wchar_t newPassword[LM20_PWLEN+2];newPassword[0] = '\0';

    printf("UserName:");
    fgetws(userName,22,stdin);
    if(userName[wcslen(userName)-1] == '\n'){
        userName[wcslen(userName)-1] = '\0';

    }

    if(wStringCheck(userName) == 1){
        printf("\n");
        return;

    }

    if(wcslen(userName) > 20){
        printf("User name is too long!\n\n");
        return;

    }

    fflush(stdin);
    printf("OldPassword:");
    fgetws(oldPassword,LM20_PWLEN+2,stdin);
    if(oldPassword[wcslen(oldPassword)-1] == '\n'){
        oldPassword[wcslen(oldPassword)-1] = '\0';

    }

    if(wcslen(oldPassword) > 14){
        printf("Old password is too long!\n\n");
        return;

    }

    fflush(stdin);
    printf("NewPassword:");
    fgetws(newPassword,LM20_PWLEN+2,stdin);
    if(newPassword[wcslen(newPassword)-1] == '\n'){
        newPassword[wcslen(newPassword)-1] = '\0';

    }

    if(wcslen(newPassword) > 14){
        printf("New password is too long!\n\n");
        return;

    }

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

void changeConsoleFontSize(char* direction){
    HANDLE consoleHandler;
    CONSOLE_FONT_INFOEX textFontInformation;
    textFontInformation.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    DWORD error = 0;
    if((consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("ChangeConsoleFontSizeGetStdHandleError:%lu\n",error);
        return;

    }

    if(GetCurrentConsoleFontEx(consoleHandler,FALSE,&textFontInformation) == FALSE){
        error = GetLastError();
        printf("ChangeConsoleFontSizeGetCurrentConsoleFontExError:%lu\n",error);
        return;

    }
    printf("Current Size:\nX:%d\nY:%d\n",textFontInformation.dwFontSize.X,textFontInformation.dwFontSize.Y);

    if(strcmp(direction,"up") == 0){
        textFontInformation.dwFontSize.X ++;
        textFontInformation.dwFontSize.Y = textFontInformation.dwFontSize.X*2;

    }

    if(strcmp(direction,"down") == 0){
        if(textFontInformation.dwFontSize.X >= 5){
        textFontInformation.dwFontSize.X --;
        textFontInformation.dwFontSize.Y = textFontInformation.dwFontSize.X*2;
        }

    }

    printf("Newest Size:\nX:%d\nY:%d\n",textFontInformation.dwFontSize.X,textFontInformation.dwFontSize.Y);
    if(SetCurrentConsoleFontEx(consoleHandler,TRUE,&textFontInformation) == FALSE){
        error = GetLastError();
        printf("ChangeConsoleFontSizeSetCurrentConsoleFontExError:%lu\n",error);
        return;

    }

}

void logOff(){
    DWORD error = 0;
    if(ExitWindowsEx(EWX_LOGOFF,0) == FALSE){
        printf("LogOffError:%lu\n\n",error);
        return;

    }

}

void lockStation(){
    DWORD error = 0;
    if(LockWorkStation() == FALSE){
        printf("LockStationError:%lu\n\n",error);
        return;

    }

}

void shutDown(wchar_t* mode){
    unsigned int operation = 0;
    HANDLE tokenHandle;
    TOKEN_PRIVILEGES tokenPriv;

    DWORD error = 0 ;
    if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&tokenHandle) == 0){
        error = GetLastError();
        printf("ShutDownOpenProcessTokenError:%lu\n",error);
        return;

    }

    if(LookupPrivilegeValueW(NULL,L"SeShutdownPrivilege",&tokenPriv.Privileges[0].Luid) == 0){
        error = GetLastError();
        printf("ShutDownLookupPrivilegeValueError:%lu\n",error);
        return;

    }

    tokenPriv.PrivilegeCount = 1;
    tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if(AdjustTokenPrivileges(tokenHandle,FALSE,&tokenPriv,0,NULL,NULL) == 0){
        error = GetLastError();
        printf("ShutDownAdjustTokenPrivilegesError:%lu\n",error);
        return;

    }

    if(wcscmp(mode,L"restart") == 0){
        operation = EWX_REBOOT;

    }else{
        operation = EWX_POWEROFF;
    }

    if(ExitWindowsEx(operation | EWX_FORCE,SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_FLAG_PLANNED) == 0){
        error = GetLastError();
        printf("ShutDownExitWindowsExError:%lu\n",error);
        return;

    }

}

command* addCommand(command* root,char* newCommandName){
    HANDLE processHeap = NULL;
    if((processHeap = getProcessHeapChecker()) == NULL){
        return NULL;

    }

    command* newCommand;
    if((newCommand = (command*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(command))) == NULL){
            printf("AddCommandHeapAllocError!\n");
            ExitProcess(1);

    }

    if((newCommand->commandName = (char*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(newCommandName) + 1)) == NULL){
            printf("AdaugaFisierHeapAllocError!\n");
            ExitProcess(1);

    }

    strcpy(newCommand->commandName,newCommandName);
    newCommand->nextCommand = NULL;

    if(root == NULL){
        return newCommand;

    }else{
        command* aux;
        for(aux = root;aux != NULL;aux = aux->nextCommand){
            if(aux->nextCommand == NULL){
                aux->nextCommand = newCommand;
                return root;
            }

        }

    }

    return root;
}

void grep(){
    forkk(L"grepCL.exe",L"");

}


void mergeFiles(){
    forkk(L"mergeCL.exe",L"");

}

void mergePartOfFiles(){
    forkk(L"mergePCL.exe",L"");

}

void filesDiferences(){
    forkk(L"diffCL.exe",L"");

}

void init(unsigned long long v[]){
for(int i=0;i<=93;i++)
     v[i]=-1;

}

unsigned long long values[94];
unsigned long long f;
unsigned long long fibonacci(int n){
    if(n < 0){
        printf("Invalid value!\n\n");
        return 4;

    }

    if(n > 93){
        printf("Overflow!\n\n");
        return 4;

    }

    if(values[n]!=-1)
        return values[n];

    if(n<=2){
        if(n)
            f=1;

        else
            f=0;
    }
    else f=fibonacci(n-1)+fibonacci(n-2);

    values[n]=f;
    return f;

}

void printFibonacci(){
    int n;
    unsigned long long result;
    printf("N:");scanf("%d",&n);
    result = fibonacci(n);
    if(result == 4){
        return;

    }
    printf("Result:%llu\n\n",result);

}

void getPartitions(){

    DWORD partitionNumber = 0;
    DWORD partitions = 0;

    if((partitions = GetLogicalDrives()) == FALSE){
        partitions = GetLastError();
        printf("GetPartitionsGetLogicalDrivesError:%lu\n\n",partitions);
        return;

    }

    printf("List of partitions:\n");
    for(int i = 0;i <= 26;i++){
        if(partitions & (1<<i)){
            partitionNumber++;
            printf("%c:\\\n",i+65);

        }

    }

    printf("\n");

}
