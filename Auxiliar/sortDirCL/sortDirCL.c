#include <stdio.h>
#include <Windows.h>
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"
#include "..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Logger\Logger.h"

typedef struct fisier{

wchar_t* nume;
struct fisier* urm;

}fisier;

typedef struct extensie{

wchar_t* nume;
struct extensie* urm;

}extensie;


fisier *rootF=NULL;
extensie *rootE=NULL;

BOOL createDirectory(wchar_t* absolutePath){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

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

void renameFile(wchar_t* oldName,wchar_t* newName){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

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

void adaugaFisier(wchar_t* nume){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

    HANDLE localProcessHeap = NULL;
    if((localProcessHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    //Alocarea de memorie pentru noul fisier plus copierea datelor necesare in noul fisier(numele fisierului).
    fisier* nou;
    if((nou = (fisier*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,sizeof(fisier))) == NULL){
            printf("AdaugaFisierHeapAllocError!\n");
            ExitProcess(1);

    }

    if((nou->nume = (wchar_t*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,MAX_PATH*2)) == NULL){
            printf("AdaugaFisierHeapAllocError!\n");
            ExitProcess(1);

    }
    wcscpy(nou->nume,nume);

    //Aici se face legatura corespunzatoare adaugarii in lista de fisiere.Adaugarea este implementata la stanga adica noul nod creat va deveni intotdeauna noua radacina.
    if(rootF!=NULL){
        nou->urm=rootF;
        rootF=nou;
    }else{
        rootF=nou;
        rootF->urm=NULL;
    }

}


///Functia cautareExtensie.
//Aceasta functie cauta existenta unei extensii in lista de extensii,extensie data prin numele sau.
int cautareExtensie(wchar_t *nume){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

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
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

    HANDLE localProcessHeap = NULL;
    if((localProcessHeap = getProcessHeapChecker()) == NULL){
        return;

    }

    wchar_t ext[10];
    wcscpy(ext,nume);


    //In cele de mai jos se fac atribuirile necesare adaugarii noului nod in lista,asta in cazul in care nu exista deja o extensie identica
    if(cautareExtensie(ext)==0){//ca valoare a numelui cu cea de mai sus.
        extensie *nou=malloc(sizeof(extensie));
        if((nou = (extensie*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,sizeof(extensie))) == NULL){
            printf("AdaugaExtensieHeapAllocError!\n");
            ExitProcess(1);

        }

        if((nou->nume = (wchar_t*)HeapAlloc(localProcessHeap,HEAP_ZERO_MEMORY,20)) == NULL){
            printf("AdaugaFisierHeapAllocError!\n");
            ExitProcess(1);

        }

        wcscpy(nou->nume,ext);


        if(rootE!=NULL){
            nou->urm=rootE;
            rootE=nou;
        }else{
            rootE=nou;
            rootE->urm=NULL;
        }

    }

}


int ultimaAparitie(wchar_t* fisier,wchar_t c){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

    int index=-1;
    int i;
    for(i=0;i<wcslen(fisier);i++){

        if(fisier[i] == c){
            index=i;
        }
    }

    return index;
}

///Functia preluareDate.
//Aceasta functie preia datele din directorul dorit a fi sortat(fisiere si extensiile corespunzatoare).
void preluareDate(wchar_t *path){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

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

        printf("Error:%lu\n",error);
        ExitProcess(error);

    }

    do{
        if((wcscmp(fileInfo.cFileName,L".") == 0) || (wcscmp(fileInfo.cFileName,L"..") == 0)){
            continue;

        }

        if(!(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
            if(wcscmp(L"sortDir.exe",fileInfo.cFileName) != 0){
                adaugaFisier(fileInfo.cFileName);
                int i = ultimaAparitie(fileInfo.cFileName,'.');
                
                if(i != -1)
                {
                    adaugaExtensie(fileInfo.cFileName+i+1);
                }else
                {
                    adaugaExtensie(L"noextension");
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

///Functia listare
//Listeaza fisierele si extensiile din liste.
void listare(){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

    fisier *auxF;
    extensie *auxE;

    printf("Fisierele continute sunt:");
    for(auxF=rootF;auxF!=NULL;auxF=auxF->urm){

        wprintf(L"%s   ",auxF->nume);

    }

    printf("\n\n");
    printf("Extensiile obtinute:");
    for(auxE=rootE;auxE!=NULL;auxE=auxE->urm){

        wprintf(L"%s   ",auxE->nume);

    }

    printf("\n\n\n");
}


///Functia creeazaDirectoare.
//Aceasta functie creeaza directoarele specifice extensiilor.
void creeazaDirectoare(wchar_t* cale){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

    wchar_t directoryFullPath[MAX_PATH];

    extensie* auxE;

    for(auxE=rootE;auxE!=NULL;auxE=auxE->urm){
        directoryFullPath[0]='\0';
        wcscat_s(directoryFullPath,sizeof(directoryFullPath),cale);
        wcscat_s(directoryFullPath,sizeof(directoryFullPath),L"\\");
        wcscat_s(directoryFullPath,sizeof(directoryFullPath),auxE->nume);
        createDirectory(directoryFullPath);
        LogW(L"sortDirCL", L"sordDirCl.c", INFOW, directoryFullPath);

    }

    printf("\n");
}

///Functia mutaFisiere.
//Aceasta functie muta un fisier in directorul cu extensia specifica fisierului.
void mutaFisiere(wchar_t *cale){
    LogA("sortDirCL", __FILE__, INFOA, __FUNCTION__);

    fisier *auxF;
    extensie *auxE;
    wchar_t cale1[MAX_PATH];
    wchar_t cale2[MAX_PATH];

    for(auxF=rootF;auxF!=NULL;auxF=auxF->urm){
        for(auxE=rootE;auxE!=NULL;auxE=auxE->urm){
            int index = ultimaAparitie(auxF->nume, '.');
            int auxiliar = index == -1 ? 0 : index; 
            if(wcscmp(auxF->nume + auxiliar + 1, auxE->nume) == 0 || (wcscmp(auxE->nume, L"noextension") == 0 && index == -1)){
                cale1[0]='\0';
                cale2[0]='\0';
                wcscat_s(cale1,sizeof(cale1),cale);
                wcscat_s(cale1,sizeof(cale1),L"\\");
                wcscat_s(cale1,sizeof(cale1),auxF->nume);

                wcscat_s(cale2,sizeof(cale2),cale);
                wcscat_s(cale2,sizeof(cale2),L"\\");
                wcscat_s(cale2,sizeof(cale2),auxE->nume);
                wcscat_s(cale2,sizeof(cale2),L"\\");
                wcscat_s(cale2,sizeof(cale2),auxF->nume);
                renameFile(cale1,cale2);

            }

        }

    }


}

int main(int argc, char* argv[]){
    LogA("sortDirCL", __FILE__, INFOA, "Starting sorting by directories operations!");

    LPWSTR commandLineString;
    commandLineString = GetCommandLineW();
    wchar_t separators[2] = L" ";
    wchar_t* sortPath;
    sortPath = wcstok(commandLineString, separators);
    wcscpy(sortPath, commandLineString + wcslen(sortPath) + 1);
    sortPath[wcslen(sortPath) - 1] = '\0';

    int length = wcslen(sortPath);
    for(int i = 0; i <= length-1;i++){
        sortPath[i] = sortPath[i+1];

    }

    if(wcslen(sortPath) > 247){
        printf("File name is too long!\n");
        return 1;

    }

    if(wExist(sortPath, L"") == 0){
        printf("The system cannot find the file specified.\n");
        ExitProcess(ERROR_FILE_NOT_FOUND);

    }

    preluareDate(sortPath);

    creeazaDirectoare(sortPath);

    mutaFisiere(sortPath);

    return 0;
}
