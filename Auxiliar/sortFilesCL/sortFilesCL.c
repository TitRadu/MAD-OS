#include <stdio.h>
#include <Windows.h>
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"
#include "..\..\Helpers\WcharHelper\WcharHelper.h"

typedef struct extensie{

wchar_t* nume;
int count;
struct extensie* urm;

}extensie;

extensie *rootE=NULL;

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

///Functia cautareExtensie.
//Aceasta functie cauta existenta unei extensii in lista de extensii,extensie data prin numele sau.
int cautareExtensie(wchar_t *nume){
    if(rootE==NULL){//Verificam daca radacina este NULL.

        return 0;//Daca este returnam 0.
    }

    extensie *aux;
    for(aux=rootE;aux!=NULL;aux=aux->urm){//Parcurgeam lista de extensii.
        if(wcscmp(aux->nume,nume)==0)//Verificam existenta extensiei cu numele dat.
            return 1;//Evident,daca gasim extensia in lista returnam 1.


    }

    return 0;//In cazul in care nu gasim extensia in lista,returnam 0.

}

///Functia adaugaExtensie.
//Aceasta functie adauga o extensie in lista de extensii.Nu vor exista noduri ce au aceeasi valoarea a numelui.
void adaugaExtensie(wchar_t *nume){
    HANDLE localProcessHeap = NULL;
    if((localProcessHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    //In cele de mai jos se fac atribuirile necesare adaugarii noului nod in lista,asta in cazul in care nu exista deja o extensie identica
    if(cautareExtensie(nume)==0){//ca valoare a numelui cu cea de mai sus.
        extensie *nou=malloc(sizeof(extensie));
        if((nou = (extensie*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,sizeof(extensie))) == NULL){
            printf("AdaugaExtensieHeapAllocError!\n");
            ExitProcess(1);

        }

        if((nou->nume = (wchar_t*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,20)) == NULL){
            printf("AdaugaFisierHeapAllocError!\n");
            ExitProcess(1);

        }

        wcscpy(nou->nume,nume);
        nou->count = 0;

        if(rootE!=NULL){
            nou->urm=rootE;
            rootE=nou;
        }else{
            rootE=nou;
            rootE->urm=NULL;
        }

    }

}

///Functia preluareDate.
//Aceasta functie preia datele din directorul dorit a fi sortat(extensiile corespunzatoare).
void preluareDate(wchar_t *path){
    HANDLE localProcessHeap = NULL;
    if((localProcessHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    HANDLE hd;
    WIN32_FIND_DATAW fileInfo;
    wchar_t starPath[MAX_PATH];
    starPath[0] = '\0';
    wcscat_s(starPath,sizeof(starPath),path);
    wcscat_s(starPath,sizeof(starPath),L"\\*");

    DWORD error = 0;
    if((hd = FindFirstFileW(starPath,&fileInfo)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_ACCESS_DENIED){
            printf("You don't have permission to parse the given directory!\n");
            ExitProcess(error);

        }
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            ExitProcess(error);

        }
        if(error == ERROR_DIRECTORY){
            printf("Sort path is a regular file!\n");
            ExitProcess(error);

        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("The system cannot find the file specified.\n");
            ExitProcess(error);

        }

        printf("Error:%lu\n",error);
        ExitProcess(error);

    }

    do{
        if((wcscmp(fileInfo.cFileName,L".") == 0) || (wcscmp(fileInfo.cFileName,L"..") == 0)){
            continue;

        }

        if(!(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
            if(wcscmp(L"sortFilesCL.exe",fileInfo.cFileName) != 0){
                int i;
                i=wLastAparition(fileInfo.cFileName,'.');
                adaugaExtensie(fileInfo.cFileName+i);
                extensie* aux;

                wchar_t* oldName;
                if((oldName = (wchar_t*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,MAX_PATH*sizeof(wchar_t))) == NULL){
                    printf("AdaugaFisierHeapAllocError!\n");
                    ExitProcess(1);

                }

                wchar_t* newName;
                if((newName = (wchar_t*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,MAX_PATH*sizeof(wchar_t))) == NULL){
                    printf("AdaugaFisierHeapAllocError!\n");
                    ExitProcess(1);

                }

                wchar_t* renameNumber;
                if((renameNumber = (wchar_t*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,4*sizeof(wchar_t))) == NULL){
                    printf("AdaugaFisierHeapAllocError!\n");
                    ExitProcess(1);

                }

                for(aux = rootE;aux != NULL;aux = aux->urm){
                    if(wcscmp(aux->nume,fileInfo.cFileName+i) == 0){
                        aux->count++;
                        wcscpy_s(oldName,MAX_PATH*sizeof(wchar_t),path);
                        wcscat_s(oldName,MAX_PATH*sizeof(wchar_t),L"\\");
                        wcscat_s(oldName,MAX_PATH*sizeof(wchar_t),fileInfo.cFileName);
                        _itow_s(aux->count,renameNumber,4*sizeof(wchar_t),10);
                        wcscpy_s(newName,MAX_PATH*sizeof(wchar_t),path);
                        wcscat_s(newName,MAX_PATH*sizeof(wchar_t),L"\\file");
                        wcscat_s(newName,MAX_PATH*sizeof(wchar_t),renameNumber);
                        wcscat_s(newName,MAX_PATH*sizeof(wchar_t),fileInfo.cFileName+i);
                        renameFile(oldName,newName);

                    }

                }

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

int main(int argc, char*argv[]){
    LPWSTR commandLineString;
    commandLineString = GetCommandLineW();
    wchar_t separators[2] = L" ";
    wchar_t* part;
    part = wcstok(commandLineString,separators);
    wcscpy(part,commandLineString + wcslen(part) + 1);
    part[wcslen(part) - 1] = '\0';

    int length = wcslen(part);
    for(int i = 0; i <= length-1;i++){
        part[i] = part[i+1];

    }

    if(wcslen(part) > 247){
        printf("File name is too long!\n");
        return 1;

    }

    if(wExist(part,L"") == 0){
        printf("The system cannot find the file specified.\n");
        ExitProcess(ERROR_FILE_NOT_FOUND);

    }

    preluareDate(part);

}
