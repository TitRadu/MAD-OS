#include "ConsoleProprierties.h"

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