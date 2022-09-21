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

HANDLE processHeap = NULL;
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

int allSpaces(char* string){
    for(int i = 0;i < strlen(string);i++){
        if(string[i] != 32){
            return 0;

        }
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

int stringCheck(char* string){
    if(strcmp(string,"") == 0 || allSpaces(string) == 1){
        printf("Argument is empty or contains only spaces!\n");
        return 1;

    }

    return 0;

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

wchar_t* wStringLastPart(wchar_t* string,wchar_t c){
    int index = 0;
    index = wLastAparition(string,c);

    if(index != -1){
        wcscpy_s(string,sizeof(wchar_t)*MAX_PATH,string+index);
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

    wchar_t commandLine[MAX_PATH*2];
    wcscpy_s(commandLine,sizeof(commandLine),L"\"");
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
        if(error == 740){
            printf("You don't have permission to do this operation.Please run command line as administrator!\n\n");
            return;

        }

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

    if(strcmp(control,"chdir") == 0){
        createHiddenDirectory(absolutePath);
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
        createFile(absolutePath, FILE_ATTRIBUTE_NORMAL);
        return;

    }

    if(strcmp(control,"chfile") == 0){
        createFile(absolutePath, FILE_ATTRIBUTE_HIDDEN);
        return;

    }

    if(strcmp(control,"rfile") == 0){
        removeFile(absolutePath);
        return;

    }

    if(strcmp(control,"hide") == 0){
        setFileProperties(absolutePath, "hide");
        return;

    }

    if(strcmp(control,"show") == 0){
        setFileProperties(absolutePath, "show");
        return;

    }

}

void fileOperationWraper(wchar_t* path, char* control){
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

BOOL createDirectory(wchar_t* absolutePath){
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return FALSE;

    }

    DWORD error = 0;
    if(CreateDirectoryW(absolutePath,NULL) == 0){
        error = GetLastError();
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return FALSE;

        }

        if(error == ERROR_ALREADY_EXISTS){
            printf("The file already exists!\n");
            return FALSE;

        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return FALSE;

        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Permission denied!\n");
            return FALSE;

        }

        if(error == ERROR_FILENAME_EXCED_RANGE){
            printf("File name is too long!\n");
            return FALSE;

        }

        printf("CreateDirectoryCreateDirectoryError:%lu\n",error);
        return FALSE;

    }

    return TRUE;
}

void createHiddenDirectory(wchar_t* absolutePath){
    if(!createDirectory(absolutePath)){
        return;

    }

    setFileProperties(absolutePath, "hide");

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

void createFile(wchar_t* absolutePath, unsigned int fileVisibility){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    DWORD error = 0;
    HANDLE createFileHandler = NULL;
    if((createFileHandler = CreateFileW(absolutePath, GENERIC_WRITE, 0, NULL,CREATE_NEW, fileVisibility, NULL)) == INVALID_HANDLE_VALUE){
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

BOOL changeFileAttributtes(PDWORD attributes, char* operation){
    if(strcmp(operation,"hide") == 0){
        if((*attributes & 0x02) == 0){
            *attributes += 0x02;
            return TRUE;

        }else{
            printf("File is already invisible!\n\n");
            return FALSE;

        }

    }

    if(strcmp(operation,"show") == 0){
        if((*attributes & 0x02) == 0x02){
            *attributes -= 0x02;
            return TRUE;

        }else{
            printf("File is already visible!\n\n");
            return FALSE;

        }

    }

    printf("Invalid operation!\n");
    return FALSE;

}

void setFileProperties(wchar_t* absolutePath, char* operation){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    DWORD attributes = 0;
    DWORD error = 0;

    if((attributes = GetFileAttributesW(absolutePath)) == INVALID_FILE_ATTRIBUTES){
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
            printf("Access is denied!\n");
            return;
        }

        printf("GetFilePropertiesGetFileAttributesWError:%lu\n",error);
        return;

    }

    printf("Current proprieties value: %lu\n", attributes);

    if(changeFileAttributtes(&attributes, operation) == FALSE){
        return;

    }

    if(SetFileAttributesW(absolutePath, attributes) == FALSE){
        error = GetLastError();
        printf("SetFilePropertiesSetFileAttributesWError:%lu\n",error);
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
    if((existCheck=wExist(program,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 1 || existCheck == 2){
        printf("First argument is a file(regular file or directory)!\n");
        return;
    }

    wchar_t openFileName[MAX_PATH];
    printf("FileName:");
    fgetws(openFileName,MAX_PATH,stdin);
    if(openFileName[wcslen(openFileName)-1] == '\n'){
        openFileName[wcslen(openFileName)-1] = '\0';

    }

    if(wStringCheck(openFileName) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,openFileName)) == NULL){
        return;

    }

    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;
    }

    if((existCheck=wExist(absolutePath,L"")) == 3){
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

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

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

void run(wchar_t* path){
    wchar_t executable[MAX_PATH];
    printf("Executable:");
    fgetws(executable,MAX_PATH,stdin);
    if(executable[wcslen(executable)-1] == '\n'){
        executable[wcslen(executable)-1] = '\0';

    }


    if(wStringCheck(executable) == 1){
        return;

    }

    wchar_t* executableAbsolutePath;
    if((executableAbsolutePath = preparePathDependingOnType(path,executable)) == NULL){
        return;

    }

    if(wcslen(executableAbsolutePath) >= MAX_PATH -1){
        printf("Executable name is too long!\n");
        return;
    }

    int existCheck = 0;
    if((existCheck=wExist(executableAbsolutePath,L"")) == 3){
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
            wchar_t argumentList[MAX_PATH];
            printf("List of arguments:");
            fgetws(argumentList,MAX_PATH,stdin);
            if(argumentList[wcslen(argumentList)-1] == '\n'){
                argumentList[wcslen(argumentList)-1] = '\0';

            }
            forkk(executableAbsolutePath,argumentList);


        }else{

            printf("First argument is a non-executable file!\n\n");
            return;

        }

    }

    if(heapFreeChecker(processHeap,0,executableAbsolutePath) == FALSE){
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

void openPathWraper(wchar_t* path){
    wchar_t openFileName[MAX_PATH];
    fgetws(openFileName,MAX_PATH,stdin);
    if(openFileName[wcslen(openFileName)-1] == '\n'){
        openFileName[wcslen(openFileName)-1] = '\0';

    }

    openPath(path,openFileName);

}

void openPath(wchar_t* path, wchar_t *openFileName){
    if(wStringCheck(openFileName) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,openFileName)) == NULL){
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

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

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

    forkk(L"sortFilesCL.exe",arguments);

}


void sortDirectory(){
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

void cryptFile(){
    forkk(L"cryptFileCL.exe",L"");

}

void decryptFile(){
    forkk(L"decryptFileCL.exe",L"");

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

void timerUp(){
    ULONGLONG startTime = 0;
    ULONGLONG currentTime = 0;
    ULONGLONG timerTime = 0;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    char oneDigitSeconds[2];
    char oneDigitMinutes[2];
    char oneDigitHours[2];

    startTime = GetTickCount64();
    while(1){
        currentTime = GetTickCount64();


        timerTime = currentTime-startTime;
        seconds = (timerTime/1000) % 60;
        minutes = (timerTime / 60000) % 60;
        hours = timerTime / 3600000;

        if (hours < 10) {
            oneDigitHours[0] = '0';
            oneDigitHours[1] = '\0';

        } else {
            oneDigitHours[0] = '\0';
        }

        if (minutes < 10) {
            oneDigitMinutes[0] = '0';
            oneDigitMinutes[1] = '\0';

        } else {
            oneDigitMinutes[0] = '\0';

        }

        if (seconds < 10) {
            oneDigitSeconds[0] = '0';
            oneDigitSeconds[1] = '\0';

        } else {
            oneDigitSeconds[0] = '\0';

        }

        printf("\r%s%d:%s%d:%s%d",oneDigitHours,hours,oneDigitMinutes,minutes,oneDigitSeconds,seconds);
        if(_kbhit()){
            printf("\n");
            break;

        }

    }

}

void timerDown(){
    int timerTimeValueInSeconds;
    ULONGLONG startTime;
    ULONGLONG currentTime;
    UINT remainingTimerTime;

    printf("Counter time:");
    scanf("%d",&timerTimeValueInSeconds);

    startTime = GetTickCount64();
    while(1){
        currentTime = GetTickCount64();

        remainingTimerTime = (timerTimeValueInSeconds) - ((currentTime - startTime)/1000);

        if(remainingTimerTime == 0){

            printf("\rCountdown:0\n");
            while(1){
                Beep(750, 1000);
                if(_kbhit()){
                    printf("\n");
                    return;

                }

            }

        }

          if(_kbhit()){
                    printf("\n");
                    return;

                }

        printf("\rCountdown:%u ",remainingTimerTime);

    }

}


void activeTime(){
    ULONGLONG activeTime;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    char oneDigitSeconds[2];
    char oneDigitMinutes[2];
    char oneDigitHours[2];


    activeTime = GetTickCount64();
    seconds = (activeTime/1000) % 60;
    minutes = (activeTime / 60000) % 60;
    hours = activeTime / 3600000;

    if (hours < 10) {
        oneDigitHours[0] = '0';
        oneDigitHours[1] = '\0';

    } else {
        oneDigitHours[0] = '\0';
    }

    if (minutes < 10) {
        oneDigitMinutes[0] = '0';
        oneDigitMinutes[1] = '\0';

    } else {
        oneDigitMinutes[0] = '\0';

    }

    if (seconds < 10) {
        oneDigitSeconds[0] = '0';
        oneDigitSeconds[1] = '\0';

    } else {
        oneDigitSeconds[0] = '\0';

    }

    printf("%s%d:%s%d:%s%d\n",oneDigitHours,hours,oneDigitMinutes,minutes,oneDigitSeconds,seconds);

}



void copyDirectoryWraper(wchar_t* path,char* control){
    wchar_t sourcePath[MAX_PATH];
    printf("SourceDirectory:");
    fgetws(sourcePath,MAX_PATH,stdin);
    if(sourcePath[wcslen(sourcePath)-1] == '\n'){
        sourcePath[wcslen(sourcePath)-1] = '\0';

    }

    if(wStringCheck(sourcePath) == 1){
        return;

    }

    wchar_t* absoluteSourcePath;
    if((absoluteSourcePath = preparePathDependingOnType(path,sourcePath)) == NULL){
        return;

    }

    if(wcslen(absoluteSourcePath) > 247){
        printf("File name is too long!\n");
        return;

   }

    int existCheck = 0;
    if((existCheck=wExist(absoluteSourcePath,L"")) == 3){
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

    wchar_t* absoluteDestinationPath;
    if((absoluteDestinationPath = preparePathDependingOnType(path,destinationPath)) == NULL){
        return;

    }

    if(wcslen(absoluteDestinationPath) > 247){
        printf("File name is too long!\n\n");
        return;

   }

    if((existCheck=wExist(absoluteDestinationPath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck != 0){
        printf("The file already exists!\n");
        return;

    }

    copyDirectory(absoluteSourcePath,absoluteDestinationPath);

    if(strcmp(control,"cut") == 0){
        removeDirectoryRecursive(absoluteSourcePath);

    }

    if(heapFreeChecker(processHeap,0,absoluteSourcePath) == FALSE){
        return;

    }

    if(heapFreeChecker(processHeap,0,absoluteDestinationPath) == FALSE){
        return;

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
    wchar_t backUpFileName[MAX_PATH];
    printf("File to backup:");
    fgetws(backUpFileName,MAX_PATH,stdin);
    if(backUpFileName[wcslen(backUpFileName)-1] == '\n'){
        backUpFileName[wcslen(backUpFileName)-1] = '\0';

    }

    if(wStringCheck(backUpFileName) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,backUpFileName)) == NULL){
        return;

    }

    backup(absolutePath);

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

}

void backup(wchar_t* absolutePath){
    if(wcslen(absolutePath) >= MAX_PATH - 1){
        printf("File name is too long!\n\n");
        return;

   }

    wchar_t absolutePathCopy[MAX_PATH];
    wcscpy_s(absolutePathCopy,sizeof(absolutePathCopy),absolutePath);
    wchar_t* lastPart = wStringLastPart(absolutePathCopy,'\\');

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
    wcscat_s(backupPath,sizeof(backupPath),lastPart);

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

    HANDLE hideInput;
    DWORD error = 0;
    if((hideInput = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    DWORD mode = 0;
    if(GetConsoleMode(hideInput,&mode) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    if(SetConsoleMode(hideInput,mode & (~ENABLE_ECHO_INPUT)) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    wchar_t userPassword[LM20_PWLEN+2];
    userPassword[0] = '\0';

    printf("UserPassword:");
    fgetws(userPassword,LM20_PWLEN+2,stdin);
    if(userPassword[wcslen(userPassword)-1] == '\n'){
        userPassword[wcslen(userPassword)-1] = '\0';

    }

    printf("\n");

    if(SetConsoleMode(hideInput,mode | ENABLE_ECHO_INPUT) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    if(wcslen(userPassword) > 14){
        printf("Password is too long!\n\n");
        return;

    }

    addUser(userName,userPassword);

}

void addUser(wchar_t* userName,wchar_t* userPassword){
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

    HANDLE hideInput;
    DWORD error = 0;
    DWORD mode = 0;
    if((hideInput = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    if(GetConsoleMode(hideInput,&mode) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    if(SetConsoleMode(hideInput,mode & (~ENABLE_ECHO_INPUT)) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    printf("OldPassword:");
    fgetws(oldPassword,LM20_PWLEN+2,stdin);
    if(oldPassword[wcslen(oldPassword)-1] == '\n'){
        oldPassword[wcslen(oldPassword)-1] = '\0';

    }
    printf("\n");

    if(SetConsoleMode(hideInput,mode | ENABLE_ECHO_INPUT) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }


    if(wcslen(oldPassword) > 14){
        printf("Old password is too long!\n\n");
        return;

    }

    fflush(stdin);

    mode = 0;
    if(GetConsoleMode(hideInput,&mode) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    if(SetConsoleMode(hideInput,mode & (~ENABLE_ECHO_INPUT)) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

    }

    printf("NewPassword:");
    fgetws(newPassword,LM20_PWLEN+2,stdin);
    if(newPassword[wcslen(newPassword)-1] == '\n'){
        newPassword[wcslen(newPassword)-1] = '\0';

    }
    printf("\n");

    if(SetConsoleMode(hideInput,mode | ENABLE_ECHO_INPUT) == 0){
        error = GetLastError();
        printf("Error:%lu\n",error);
        return;

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
    command* newCommand;
    if((newCommand = (command*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(command))) == NULL){
            printf("AddCommandHeapAllocError!\n");
            ExitProcess(1);

    }

    if((newCommand->commandName = (char*)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,strlen(newCommandName) + 1)) == NULL){
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
    printf("Result:%I64u\n\n",result);

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

void displayComputerName(){
    DWORD PCsize = THIRTY;
    wchar_t PCname[THIRTY];
    DWORD error = 0;

    if(!GetComputerNameExW(ComputerNamePhysicalDnsHostname, PCname,&PCsize)){
        error = GetLastError();
        printf("DisplayComputerNameGetComputerNameError:%lu\n",error);
        ExitProcess(-1);

    }

    wprintf(L"%ls\n",PCname);

}

void setComputerNameWraper(){
    wchar_t newComputerName[THIRTY];
    fgetws(newComputerName,THIRTY,stdin);
    if(newComputerName[wcslen(newComputerName)-1] == '\n'){
        newComputerName[wcslen(newComputerName)-1] = '\0';

    }

    if(wStringCheck(newComputerName) == 1){
        return;

    }

    setComputerName(newComputerName);

}
void setComputerName(wchar_t* newComputerName){
    DWORD error = 0;

    if(!SetComputerNameExW(ComputerNamePhysicalDnsHostname, newComputerName)){
        error = GetLastError();
        printf("SetComputerNameSetComputerNameError:%lu\n",error);
        ExitProcess(-1);

    }

    printf("To see changes you need to restart the computer!\n\n");

}

void systemInformationPrint(MEMORYSTATUSEX memoryStatus, PERFORMANCE_INFORMATION performanceInformation){
    double memoryLoadPercentage = 100 - ((double)memoryStatus.ullAvailPhys / memoryStatus.ullTotalPhys)* 100 ;
    double totalPhysicalGB = (double)memoryStatus.ullTotalPhys / 1073741824;
	double avaiblePhysicalGB = (double)memoryStatus.ullAvailPhys / 1073741824;
	double totalVirtualGB = (double)memoryStatus.ullTotalVirtual / 1073741824;
	double avaibleVirtualGB = (double)memoryStatus.ullAvailVirtual / 1073741824;


    printf("MemoryLoad: %lu%%\n", memoryStatus.dwMemoryLoad);
    printf("MemoryLoad: %.2f%%\n", memoryLoadPercentage);
	printf("TotalPhys: %.2f GB\n", totalPhysicalGB);
	printf("AvailablePhys: %.2f GB\n", avaiblePhysicalGB);
	printf("TotalVirtual: %.2f GB\n", totalVirtualGB);
	printf("AvailableVirtual: %.2f GB\n", avaibleVirtualGB);
	printf("Number of processess: %lu\n", performanceInformation.ProcessCount);
	printf("Number of threads: %lu\n", performanceInformation.ThreadCount);

}

void systemInformation(){
    MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	DWORD error = 0;

	if (GlobalMemoryStatusEx(&memoryStatus) == 0){
	    error = GetLastError();
		printf("SystemInformationGlobalMemoryStatusExError:%lu\n", error);
		ExitProcess(error);

	}

	PERFORMANCE_INFORMATION performanceInformation;
    if (GetPerformanceInfo(&performanceInformation,sizeof(PERFORMACE_INFORMATION)) == 0){
        error = GetLastError();
		printf("SystemInformationGetPerformanceInfoError:%lu\n", error);
		ExitProcess(error);

	}

	systemInformationPrint(memoryStatus, performanceInformation);

}

CONSOLE_DATA consoleDataPreparing(){
    HANDLE console;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD error;

    if((console = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("ClearrGetStdHandleError:%lu\n",error);
        ExitProcess(error);

    }

    if(GetConsoleScreenBufferInfo(console,&screen) == 0){
        error = GetLastError();
        printf("ClearrGetConsoleScreenBufferError:%lu\n",error);
        ExitProcess(error);

    }

    CONSOLE_DATA consoleData;
    consoleData.consoleHandle = console;
    consoleData.currentCursorPosition =screen.dwCursorPosition;
    consoleData.screen = screen;

    return consoleData;

}

void liveSystemInformation(){
    PERFORMACE_INFORMATION performanceInformation;
    CONSOLE_DATA consoleData = consoleDataPreparing();
    DWORD error;

    CONSOLE_CURSOR_INFO consoleCursorInfo;
    if(GetConsoleCursorInfo(consoleData.consoleHandle, &consoleCursorInfo) == 0){
        error = GetLastError();
        printf("LiveSystemInformationGetConsoleCursorInfoError:%lu\n", error);
        ExitProcess(error);

    }

    consoleCursorInfo.bVisible = FALSE;

    if(SetConsoleCursorInfo(consoleData.consoleHandle, &consoleCursorInfo) == 0){
        error = GetLastError();
        printf("LiveSystemInformationSetConsoleCursorInfoError:%lu\n", error);
        ExitProcess(error);

    }

    while(1){
       if (GetPerformanceInfo(&performanceInformation,sizeof(PERFORMACE_INFORMATION)) == 0){
            error = GetLastError();
            printf("LiveSystemInformationGetPerformanceInfoError:%lu\n", error);
            ExitProcess(error);

        }


        ULONGLONG avaiblePhysicalBytes = performanceInformation.PhysicalAvailable * performanceInformation.PageSize;
        double memoryLoadPercentage = 100 - ((double) avaiblePhysicalBytes / (performanceInformation.PhysicalTotal * performanceInformation.PageSize))* 100 ;
        double avaiblePhysicalGB = (double)avaiblePhysicalBytes / 1073741824;

        printf("MemoryLoad: %.2f%%\n", memoryLoadPercentage);
        printf("AvailablePhys: %.2f GB\n", avaiblePhysicalGB);
        printf("Number of processess: %lu \n", performanceInformation.ProcessCount);
        printf("Number of threads: %lu \n", performanceInformation.ThreadCount);

        if(SetConsoleCursorPosition(consoleData.consoleHandle,consoleData.currentCursorPosition) == 0){
            error = GetLastError();
            printf("ClearrSetConsoleCursorPositionError:%lu\n",error);
            ExitProcess(error);

        }

        if(_kbhit()){
            consoleCursorInfo.bVisible = TRUE;
            if(SetConsoleCursorInfo(consoleData.consoleHandle, &consoleCursorInfo) == 0){
                error = GetLastError();
                printf("LiveSystemInformationGlobalMemoryStatusExError:%lu\n", error);
                ExitProcess(error);

            }

            consoleData.currentCursorPosition.Y = consoleData.currentCursorPosition.Y + 5;
            if(SetConsoleCursorPosition(consoleData.consoleHandle,consoleData.currentCursorPosition) == 0){
                error = GetLastError();
                printf("ClearrSetConsoleCursorPositionError:%lu\n",error);
                ExitProcess(error);

            }

            printf("\n");
            break;

        }

    }

}

void enumWlanInterfaces(){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    PWLAN_INTERFACE_INFO_LIST pwlanInterfaceInfoList = NULL;
    PWLAN_INTERFACE_INFO pwlanInterfaceInfo = NULL;
    wchar_t stringGUID[40] = {0};
    DWORD error = 0;



    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("EnumWlanInterfacesWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanEnumInterfaces(wlanHandle, NULL, &pwlanInterfaceInfoList)) != ERROR_SUCCESS){
        printf("EnumWlanInterfacesWlanEnumInterfacesError:%lu",error);
        ExitProcess(error);

    }else{
        wprintf(L"Number of interfaces: %lu\n\n", pwlanInterfaceInfoList->dwNumberOfItems);
        for(int i = 0; i < (int)pwlanInterfaceInfoList->dwNumberOfItems; i++){
            pwlanInterfaceInfo = &pwlanInterfaceInfoList->InterfaceInfo[i];
            wprintf(L" Interface index:%lu\n",i);
            error = StringFromGUID2(&pwlanInterfaceInfo->InterfaceGuid, (LPOLESTR) &stringGUID, 39);
            if(error == 0 ){
                wprintf(L"EnumWirelessInterfacesStringFromGUID2Error!");
                ExitProcess(-1);

            }else{
                wprintf(L" Interface GUID: %ls\n", stringGUID);

            }
            wprintf(L" Interface description: %ls\n", pwlanInterfaceInfo->strInterfaceDescription);
            wprintf(L" Interface state:\t");
            switch (pwlanInterfaceInfo->isState) {
            case wlan_interface_state_not_ready:
                wprintf(L"Not ready\n");
                break;
            case wlan_interface_state_connected:
                wprintf(L"Connected\n");
                break;
            case wlan_interface_state_ad_hoc_network_formed:
                wprintf(L"First node in a ad hoc network\n");
                break;
            case wlan_interface_state_disconnecting:
                wprintf(L"Disconnecting\n");
                break;
            case wlan_interface_state_disconnected:
                wprintf(L"Not connected\n");
                break;
            case wlan_interface_state_associating:
                wprintf(L"Attempting to associate with a network\n");
                break;
            case wlan_interface_state_discovering:
                wprintf(L"Auto configuration is discovering settings for the network\n");
                break;
            case wlan_interface_state_authenticating:
                wprintf(L"In process of authenticating\n");
                break;
            default:
                wprintf(L"Unknown state %ld\n", pwlanInterfaceInfo->isState);
                break;
            }
            wprintf(L"\n");

        }

    }

    if (pwlanInterfaceInfoList != NULL) {
        WlanFreeMemory(pwlanInterfaceInfoList);
        pwlanInterfaceInfo = NULL;

    }

    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("EnumWlanInterfacesWlanCloseHandleError:%lu",error);
        ExitProcess(error);

    }

}

GUID* obtainGUIDFromStringWraper(){
    wchar_t stringGUID[40] = {0};
    printf("GUID:");
    fgetws(stringGUID,40,stdin);
    if(stringGUID[wcslen(stringGUID)-1] == '\n'){
        stringGUID[wcslen(stringGUID)-1] = '\0';

    }

    return obtainGUIDFromString(stringGUID);

}

GUID* obtainGUIDFromString(wchar_t* stringGUID){
    if(wStringCheck(stringGUID) == 1){
        return NULL;

    }

    LPCLSID clsid;
    if((clsid = (LPCLSID)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(CLSID))) == NULL){
        printf("ObtainGUIDFromStringHeapAllocError!\n");
        ExitProcess(-1);

    }

    if(CLSIDFromString((LPCOLESTR) stringGUID, clsid) == E_INVALIDARG){
        printf("ObtainGUIDFromStringCLSIDFromStringError\n");
        ExitProcess(-1);

    }
    return (GUID*) clsid;

}

void sendGUIDAsParameter(char* control){
    GUID* guid;
    if((guid = obtainGUIDFromStringWraper()) == NULL){
        return;

    }

    if(strcmp(control, "networks") == 0){
        enumAvaibleNetworks(guid);

    }

    if(strcmp(control, "disconnect") == 0){
        disconnectWlanInterface(guid);

    }

    if(heapFreeChecker(processHeap,0,guid) == FALSE){
        return;

    }

}


void enumAvaibleNetworks(GUID* guid){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    PWLAN_AVAILABLE_NETWORK_LIST pwlanAvaibleNewtworkList = NULL;
    PWLAN_AVAILABLE_NETWORK pwlanAvaibleNetwork = NULL;
    int semnalQuality;
    DWORD error = 0;

    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("EnumAvaibleNetworksWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanGetAvailableNetworkList(wlanHandle, guid, 3, NULL, &pwlanAvaibleNewtworkList)) !=  ERROR_SUCCESS){

        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return;
        }
        printf("EnumAvaibleNetworksWlanGetAvaibleNetworkListError:%lu",error);
        ExitProcess(error);

    }else{
        wprintf(L"Number of networks: %lu\n\n", pwlanAvaibleNewtworkList->dwNumberOfItems);

        for(int i = 0; i < pwlanAvaibleNewtworkList->dwNumberOfItems; i++){
            pwlanAvaibleNetwork = &pwlanAvaibleNewtworkList->Network[i];
            if(pwlanAvaibleNetwork->dot11Ssid.uSSIDLength == 0){
                wprintf(L"SSID:None\n");

            }else{
                wprintf(L"SSID[%d]:",i);
                for(int j = 0; j < pwlanAvaibleNetwork->dot11Ssid.uSSIDLength; j++){
                    wprintf(L"%c",pwlanAvaibleNetwork->dot11Ssid.ucSSID[j]);


                }
                wprintf(L"\n");
                wprintf(L"Profile: %ls\n", pwlanAvaibleNetwork->strProfileName);
                wprintf(L"Security Enabled[%d]:\t ", i);
                if (pwlanAvaibleNetwork->bSecurityEnabled){
                    wprintf(L"Yes\n");

                }else{
                    wprintf(L"No\n");

                }
                 if (pwlanAvaibleNetwork->wlanSignalQuality == 0){
                    semnalQuality = -100;
                } else if (pwlanAvaibleNetwork->wlanSignalQuality == 100){
                    semnalQuality = -50;
                } else{
                    semnalQuality = -100 + (pwlanAvaibleNetwork->wlanSignalQuality/2);
                }

                wprintf(L"Signal Quality[%d]:\t %d (RSSI Strength: %d dBm)\n", i,
                    pwlanAvaibleNetwork->wlanSignalQuality, semnalQuality);

                wprintf(L"Connectable[%d]:\t ", i);
                if (pwlanAvaibleNetwork->bNetworkConnectable){
                    wprintf(L"Yes\n");
                }else {
                    wprintf(L"No\n");

                }
                printf("BSS:%d\n",pwlanAvaibleNetwork->dot11BssType);


            }
            wprintf(L"\n");

        }

    }

    if (pwlanAvaibleNewtworkList != NULL) {
        WlanFreeMemory(pwlanAvaibleNewtworkList);
        pwlanAvaibleNewtworkList = NULL;
    }

    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("EnumAvaibleNetworksWlanCloseHandleError:%lu",error);
        ExitProcess(error);

    }

}

void disconnectWlanInterface(GUID* guid){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    DWORD error = 0;

    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("DisconnectWlanInterfaceWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanDisconnect(wlanHandle, guid, NULL)) !=  ERROR_SUCCESS){

        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return;
        }

        printf("DisconnectWlanInterfaceWlanDisconnectError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("DisconnectWlanInterfaceWlanCloseHandleError:%lu",error);
        ExitProcess(error);

    }

}

PWLAN_AVAILABLE_NETWORK getNetworkProprierties(HANDLE wlanHandle, GUID* guid, char* ssidString, LPCWSTR profile){
    PWLAN_AVAILABLE_NETWORK_LIST pwlanAvaibleNewtworkList = NULL;
    WLAN_AVAILABLE_NETWORK currentAvaibleNetwork;
    PWLAN_AVAILABLE_NETWORK pwlanAvaibleNetwork;
    int networkExist = 0;
    DWORD error = 0;


    if((error = WlanGetAvailableNetworkList(wlanHandle, guid, 3, NULL, &pwlanAvaibleNewtworkList)) !=  ERROR_SUCCESS){
        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return NULL;
        }
        printf("EnumAvaibleNetworksWlanGetAvaibleNetworkListError:%lu",error);
        ExitProcess(error);

    }else{
        for(int i = 0; i < pwlanAvaibleNewtworkList->dwNumberOfItems; i++){
                currentAvaibleNetwork = pwlanAvaibleNewtworkList->Network[i];
                if((currentAvaibleNetwork.strProfileName == NULL) || (wcslen(currentAvaibleNetwork.strProfileName) == 0)){
                    continue;

                }

                char currentSSID[100];
                for(int j =0; j<pwlanAvaibleNewtworkList->Network[i].dot11Ssid.uSSIDLength; j++){
                    currentSSID[j] = pwlanAvaibleNewtworkList->Network[i].dot11Ssid.ucSSID[j];

                }

                currentSSID[pwlanAvaibleNewtworkList->Network[i].dot11Ssid.uSSIDLength] = '\0';

                if((strcmp(currentSSID, ssidString) == 0) && (wcscmp(currentAvaibleNetwork.strProfileName, profile) == 0)){
                    if((pwlanAvaibleNetwork = (PWLAN_AVAILABLE_NETWORK)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(WLAN_AVAILABLE_NETWORK))) == NULL){
                        printf("GetNetworkPropriertiesHeapAllocError!\n");
                        ExitProcess(-1);

                    }

                    CopyMemory(pwlanAvaibleNetwork, pwlanAvaibleNewtworkList->Network + i, sizeof(WLAN_AVAILABLE_NETWORK));
                    networkExist = 1;
                    break;

            }

        }

    }

    if (pwlanAvaibleNewtworkList != NULL) {
        WlanFreeMemory(pwlanAvaibleNewtworkList);
        pwlanAvaibleNewtworkList = NULL;
    }

    if(!networkExist){
        printf("A network with this parameters doesn't exist!\n\n");
        return NULL;

    }
    return pwlanAvaibleNetwork;

}

void connectWlanInterfaceWraper(){
    GUID* guid = obtainGUIDFromStringWraper();

    DOT11_SSID dot11ssid;
    printf("SSID:");
    fgets(dot11ssid.ucSSID, WLAN_MAX_NAME_LENGTH,stdin);
    if(dot11ssid.ucSSID[strlen(dot11ssid.ucSSID)-1] == '\n'){
        dot11ssid.ucSSID[strlen(dot11ssid.ucSSID)-1] = '\0';

    }
    if(stringCheck(dot11ssid.ucSSID) == 1){
        return;

    }
    dot11ssid.uSSIDLength = strlen(dot11ssid.ucSSID);

    wchar_t profile[WLAN_MAX_NAME_LENGTH] = {0};
    printf("Profile:");
    fgetws(profile,WLAN_MAX_NAME_LENGTH,stdin);
    if(profile[wcslen(profile)-1] == '\n'){
        profile[wcslen(profile)-1] = '\0';

    }
    if(wStringCheck(profile) == 1){
        return;

    }

    connectWlanInterface(guid, dot11ssid, profile);

    if(heapFreeChecker(processHeap,0,guid) == FALSE){
        return;

    }

}

void connectWlanInterface(GUID* guid, DOT11_SSID ssid, LPCWSTR profile){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    DWORD error = 0;

    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("ConnectWlanInterfaceWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    PWLAN_AVAILABLE_NETWORK connectionNetworkData = getNetworkProprierties(wlanHandle, guid, ssid.ucSSID, profile);
    if(connectionNetworkData == NULL){
        return;

    }
    WLAN_CONNECTION_PARAMETERS wlanConnectionParameters;
    wlanConnectionParameters.wlanConnectionMode = wlan_connection_mode_profile;
    //wcscpy_s(wlanConnectionParameters.strProfile, sizeof(wchar_t) * WLAN_MAX_NAME_LENGTH, profile);
    wlanConnectionParameters.strProfile = profile;
    wlanConnectionParameters.pDot11Ssid = &ssid;
    wlanConnectionParameters.pDesiredBssidList = NULL;
    wlanConnectionParameters.dot11BssType = connectionNetworkData->dot11BssType;

    if((error = WlanConnect(wlanHandle, guid, &wlanConnectionParameters, 0)) !=  ERROR_SUCCESS){

        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return;
        }

        printf("ConnectWlanInterfaceWlanDisconnectError:%lu",error);
        ExitProcess(error);

    }


    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("ConnectWlanInterfaceWlanCloseHandleError:%lu\n",error);
        ExitProcess(error);

    }

}

void enumerateBluetoothRadios(){
    HBLUETOOTH_RADIO_FIND bluetoothRadioFindHandle;
    BLUETOOTH_FIND_RADIO_PARAMS bluetoothFindRadioParams;
    bluetoothFindRadioParams.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);
    HANDLE bluetoothRadioHandle;
    DWORD error = 0;


    if((bluetoothRadioFindHandle = BluetoothFindFirstRadio(&bluetoothFindRadioParams, &bluetoothRadioHandle)) == NULL){
        error = GetLastError();
        if(error == ERROR_NO_MORE_ITEMS){
            return;

        }


        printf("EnumerateBluetoothRadiosBluetoothFindFirstRadioError: %lu\n", error);
        ExitProcess(error);

    }

    BLUETOOTH_RADIO_INFO bluetoothRadioInfo;
    bluetoothRadioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
    if((error =  BluetoothGetRadioInfo(bluetoothRadioHandle, &bluetoothRadioInfo)) != ERROR_SUCCESS){
        printf("EnumerateBluetoothRadiosBluetoothGetRadioInfoError: %lu\n", error);
        ExitProcess(error);

    }

    wprintf(L"Radio name: %ls\n", bluetoothRadioInfo.szName);
    wprintf(L"Manufacturer: %d\n", bluetoothRadioInfo.manufacturer);
    wprintf(L"Adress: %p\n\n", bluetoothRadioInfo.address.ullLong);

    while(1){
        if(BluetoothFindNextRadio(bluetoothRadioFindHandle, bluetoothRadioHandle) == FALSE){
            error = GetLastError();
            if(error == ERROR_NO_MORE_ITEMS){
                return;

            }
            printf("EnumerateBluetoothRadiosBluetoothFindNextRadioError: %lu\n", error);
            ExitProcess(error);

        }

        wprintf(L"Radio name: %ls\n", bluetoothRadioInfo.szName);
        wprintf(L"Manufacturer: %d\n", bluetoothRadioInfo.manufacturer);
        wprintf(L"Adress: %p\n\n", bluetoothRadioInfo.address.ullLong);

    }

    if(CloseHandle(bluetoothRadioHandle) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothRadiosCloseHandleError:%lu\n",error);
        return;

    }

    if(BluetoothFindRadioClose(bluetoothRadioFindHandle) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothRadiosBluetoothFindRadioCloseError:%lu", error);
        ExitProcess(error);

    }

}

void printBluetoothDeviceInformations(BLUETOOTH_DEVICE_INFO deviceInfo){
    DWORD error = 0;
    wprintf(L"Device name: %s\n", deviceInfo.szName);
    if(deviceInfo.fConnected){
        printf("Connected: YES\n");

    }else{
        printf("Connected: NO\n");

    }
    wchar_t localDate[THIRTY];
    if(GetDateFormatEx(NULL, DATE_LONGDATE, &deviceInfo.stLastUsed, NULL, localDate, sizeof(localDate)/sizeof(wchar_t), NULL ) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothDevicesGetDateFormatExError:%lu\n", error);
        ExitProcess(error);

    }
    wprintf(L"%ls ", localDate);
    if(GetTimeFormatEx(NULL, 0, &deviceInfo.stLastUsed, NULL, localDate, sizeof(localDate)/sizeof(wchar_t)) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothDevicesGetTimeFormatExError:%lu\n", error);
        ExitProcess(error);

    }
    wprintf(L"%ls\n\n", localDate);

}

void enumerateBluetoothDevices(){
    HBLUETOOTH_DEVICE_FIND bluetoothDeviceFindHandle;

    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams;
    searchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.fIssueInquiry = TRUE;
    searchParams.cTimeoutMultiplier = 1;
    searchParams.hRadio = NULL;

    BLUETOOTH_DEVICE_INFO deviceInfo;
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    DWORD error = 0;


    if((bluetoothDeviceFindHandle = BluetoothFindFirstDevice(&searchParams,&deviceInfo)) == NULL){
        error = GetLastError();
        if(error == ERROR_NO_MORE_ITEMS){
            return;

        }
        printf("EnumerateBluetoothDevicesBluetoothFindFirstDeviceError:%lu\n", error);
        ExitProcess(error);
    }

    printBluetoothDeviceInformations(deviceInfo);

    while(1){
        if(BluetoothFindNextDevice(bluetoothDeviceFindHandle, &deviceInfo) == FALSE){
        error = GetLastError();
        if(error == ERROR_NO_MORE_ITEMS){
            return;

        }

        printf("EnumerateBluetoothDevicesBluetoothFindNextDeviceError:%lu\n",error);
        ExitProcess(error);

        }

        printBluetoothDeviceInformations(deviceInfo);

    }

    if(BluetoothFindDeviceClose(bluetoothDeviceFindHandle) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothDevicesBluetoothFindDeviceCloseError:%lu", error);
        ExitProcess(error);

    }

}

void enumerateDeviceDrivers(){
    LPVOID drivers[1024];
    DWORD numberOfBytesNeeded;
    int numberOfDrivers, i;
    DWORD error = 0;

    if(EnumDeviceDrivers(drivers, sizeof(drivers), &numberOfBytesNeeded) == TRUE){
        numberOfDrivers =  numberOfBytesNeeded / sizeof(drivers[0]);

        printf("Drivers are:(base name -> file name)\n");

        WCHAR driverName[1024];
        for(i=0; i<numberOfDrivers; i++){
            if(GetDeviceDriverBaseNameW(drivers[i], driverName, sizeof(driverName)) == TRUE){
                wprintf(L"Application need some changes. Contact the development engineer!\n");
                ExitProcess(-1);

            }else{
                error = GetLastError();
                if(error == ERROR_ENVVAR_NOT_FOUND){
                    wprintf(L"%d:%s", i+1, driverName);
                    if(GetDeviceDriverFileNameW(drivers[i], driverName, sizeof(driverName)) == TRUE){
                        wprintf(L"Application need some changes. Contact the development engineer!\n");
                        ExitProcess(-1);

                    }else{
                        error = GetLastError();
                        if(error == ERROR_ENVVAR_NOT_FOUND){
                            wprintf(L" \t-> \t%s\n",driverName);
                            continue;

                        }
                        printf("EnumerateDeviceDriversGetDeviceDriverFileNameWError:%lu\nl", error);
                        ExitProcess(error);

                    }

                }
                printf("EnumerateDeviceDriversGetDeviceDriverBaseNameWError:%lu\nl", error);
                ExitProcess(error);
            }

        }

    }else{
        error = GetLastError();
        printf("EnumerateDeviceDriversEnumDeviceDriversError:%lu", error);
        ExitProcess(error);
    }
    printf("\n");

}

void imdbAdvancedSearchWrapper(){
    WCHAR title[1024];

    printf("Title:");
    fgetws(title,MAX_PATH,stdin);
    if(title[wcslen(title)-1] == '\n'){
        title[wcslen(title)-1] = '\0';

    }

    if(wStringCheck(title) == 1){
        return;

    }

    wchar_t url[41+wcslen(title)+36+1];
    url[0] = '\0';
    wcscat_s(url,sizeof(url),L"https://www.imdb.com/search/title/?title=");
    wcscat_s(url,sizeof(url),title);
    wcscat_s(url,sizeof(url),L"&title_type=feature&num_votes=10000,");

    connectToURL(url);

}

void youTubeSearchWrapper(){
    WCHAR searched[1024];

    printf("Search:");
    fgetws(searched,MAX_PATH,stdin);
    if(searched[wcslen(searched)-1] == '\n'){
        searched[wcslen(searched)-1] = '\0';

    }

    if(wStringCheck(searched) == 1){
        return;

    }

    wchar_t url[45+wcslen(searched)+1];
    url[0] = '\0';
    wcscat_s(url,sizeof(url),L"https://www.youtube.com/results?search_query=");
    wcscat_s(url,sizeof(url),searched);

    connectToURL(url);
}

