#include "GeneralRunner.h"

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

    if(existCheck){
        printf("First argument is a file(regular file or directory)!\n");
        return;

    }

    HINSTANCE error = 0;
    if((error = ShellExecuteW(NULL,L"open",program,NULL,NULL,1)) <= (HINSTANCE)32){
        if(error == (HINSTANCE)2){
            printf("Program not found!\n");
            return;

        }

        printf("Start1ShellExecuteError:%p!\n", error);
        return;

    }

}

void openFileWraper(wchar_t* path){
    wchar_t openFileName[MAX_PATH];
    fgetws(openFileName,MAX_PATH,stdin);
    if(openFileName[wcslen(openFileName)-1] == '\n'){
        openFileName[wcslen(openFileName)-1] = '\0';

    }

    openFile(path,openFileName);

}

void openFile(wchar_t* path, wchar_t *openFileName){
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

    if(!existCheck){
        printf("This path doesn't exist as file!\n");
        return;

    }

    HINSTANCE error = 0;
    if((error = ShellExecuteW(NULL,L"open",absolutePath,NULL,NULL,1)) <= (HINSTANCE)32){
        if(error == (HINSTANCE)5){
            printf("The operating system denied access to the specified file!\n");
            return;

        }

        printf("OpenPathShellExecuteError:%p!\n", error);
        return;

    }

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
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

    if(existCheck){
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

    if(!existCheck){
        printf("Second argument doesn't exist as file!\n");
        return;

    }

    if(existCheck != 1){
        printf("Second argument isn't a regular file!\n");
        return;

    }

    wStringInQuatationMarks(absolutePath);

    openFileWithProgram(program,absolutePath);

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

}

void openFileWithProgram(wchar_t* program,wchar_t* absolutePath){
    HINSTANCE error = 0;
    if((error = ShellExecuteW(NULL,L"open",program,absolutePath,NULL,1)) <= (HINSTANCE)32){
        if(error == (HINSTANCE)2){
            printf("Program not found!\n");
            return;

        }
        printf("OpenFileWithProgramShellExecuteError:%p!\n", error);
        return;

    }

}

void runWraper(wchar_t* path, BOOL isLocalMode){
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
        wchar_t argumentList[MAX_PATH];
        printf("List of arguments:");
        fgetws(argumentList,MAX_PATH,stdin);
        if(argumentList[wcslen(argumentList)-1] == '\n'){
            argumentList[wcslen(argumentList)-1] = '\0';

        }

        run(executableAbsolutePath, argumentList, isLocalMode);
    }

    if(heapFreeChecker(processHeap,0,executableAbsolutePath) == FALSE){
        return;

    }

}

void run(wchar_t* executable, wchar_t* arguments , BOOL isLocalMode){
    if(isLocalMode && wcscmp(executable+wcslen(executable)-4,L".msi") != 0){
        forkk(executable, arguments, INVALID_HANDLE_VALUE);
    }else
    {
        SetConsoleCtrlHandler(NULL,FALSE);
        if((ShellExecuteW(NULL, L"open", executable, arguments, NULL, 1)) <= (HINSTANCE)32){
            printf("ClineShellExecuteError:Error!\n");
            return;
        }
        SetConsoleCtrlHandler(NULL,TRUE);
    }
}
