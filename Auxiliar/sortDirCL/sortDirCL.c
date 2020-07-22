#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <Windows.h>
#define CMD "C:\\Windows\\System32\\cmd.exe"
#define PATH 1024

int allSpaces(char* string){
    for(int i = 0;i < strlen(string);i++){
        if(string[i] != 32){
            return 0;

        }
    }

    return 1;
}

int stringCheck(char *string){
    if(strcmp(string,"") == 0 || allSpaces(string) == 1){
        printf("First argument is empty or contains only spaces!\n");
        return 1;

    }

    return 0;

}

void forkk(char *application,char *args){
    STARTUPINFO s;
    PROCESS_INFORMATION p;
    ZeroMemory(&s,sizeof(STARTUPINFO));
    s.cb = sizeof(STARTUPINFO);
    ZeroMemory(&p,sizeof(PROCESS_INFORMATION));
    char commandLine[PATH];
    commandLine[0] = '\0';
    strcat(commandLine,application);
    strcat(commandLine," ");
    strcat(commandLine,args);



    BOOL createProccesCheck = FALSE;
createProccesCheck = CreateProcess(
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

    DWORD error = 0;
    if(createProccesCheck == FALSE){
        error = GetLastError();
        printf("CreateProcessCheck:%lu\n",error);
        ExitProcess(error);

    }

    if(WaitForSingleObject(p.hProcess,INFINITE) == WAIT_FAILED){
        error = GetLastError();
        printf("WaitForSingleObjectCheck:%lu\n",error);
        ExitProcess(error);

    }

    if(CloseHandle(p.hProcess) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

    if(CloseHandle(p.hThread) == FALSE){
        error = GetLastError();
        ExitProcess(error);

    }

}

typedef struct fisier{

char *nume;
struct fisier *urm;

}fisier;

typedef struct extensie{

char *nume;
struct extensie *urm;

}extensie;


fisier *rootF=NULL;
extensie *rootE=NULL;

void adaugaFisier(char* nume){
    fisier *nou=malloc(sizeof(fisier));//
    nou->nume=malloc(100);//Alocarea de memorie pentru noul fisier plus copierea datelor necesare in noul fisier(numele fisierului).
    strcpy(nou->nume,nume);//

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
int cautareExtensie(char *nume){
    if(rootE==NULL){//Verificam daca radacina este NULL.

        return 0;//Daca este returnam 0.
    }

    extensie *aux;
    for(aux=rootE;aux!=NULL;aux=aux->urm){//Parcurgeam lista de extensii.
        if(strcmp(aux->nume,nume)==0)//Verificam existenta extensiei cu numele dat.
            return 1;//Evident,daca gasim extensia in lista returnam 1.


    }

    return 0;//In cazul in care nu gasim extensia in lista,returnam 0.

}

///Functia adaugaExtensie.
//Aceasta functie adauga o extensie in lista de extensii.Nu vor exista noduri ce au aceeasi valoarea a numelui.
void adaugaExtensie(char *nume){

    char *ext=malloc(10);
    ext[0]='\0';
    strcat(ext,nume);


    //In cele de mai jos se fac atribuirile necesare adaugarii noului nod in lista,asta in cazul in care nu exista deja o extensie identica
    if(cautareExtensie(ext)==0){//ca valoare a numelui cu cea de mai sus.
        extensie *nou=malloc(sizeof(extensie));
        nou->nume=malloc(10);
        strcpy(nou->nume,ext);


        if(rootE!=NULL){
            nou->urm=rootE;
            rootE=nou;
        }else{
            rootE=nou;
            rootE->urm=NULL;
        }

    }
     free(ext);
}


int ultimaAparitie(char *fisier,char c){
    int index=-1;
    int i;
    for(i=0;i<strlen(fisier);i++){

        if(fisier[i] == c){
            index=i;
        }
    }

    return index;
}

///Functia preluareDate.
//Aceasta functie preia datele din directorul dorit a fi sortat(fisiere si extensiile corespunzatoare).
void preluareDate(char *path){
    //Functia opendir este folosita pentru a deschide un director.Returneaza o referinta la structura de tip DIR.
    DIR *dir = NULL;
    if((dir=opendir(path)) == NULL){
        if(errno == ENOENT){
            printf("This path doesn't exist!\n");
            ExitProcess(-1);

        }

        if(errno == ENOTDIR){
            printf("This path isn't a directory!\n");
            ExitProcess(-1);

        }

    }

    //Functia readdir citeste pe rand fiecare intrare din director(fisier sau alt director).Returneaza o referinta la o structura de tip
    //dirent.Aceasta structura contine un camp char d_name[] care va contine numele intrarii cu tot cu extensie daca aceasta e fisier.
    struct dirent *dr = NULL;
    char newpath[PATH];

    int ok=0;
    while((dr=readdir(dir)) != NULL){//Citim din director pana se ajunge la NULL.
        if((strcmp(dr->d_name,".") == 0) || (strcmp(dr->d_name,"..") == 0)){
            continue;

        }

        //Ne formam noua cale catre fiecare intrare din director,pentru a putea obtine cu ajutorul functiei stat informatii(vezi mai jos)).
        snprintf(newpath,PATH,"%s\\%s",path,dr->d_name);
        struct _stat buf;
        //Stat este o functie ce ne ofera diferite informatii despre fisierul dat ca si parametru(newpath).
        if(_stat(newpath,&buf) < 0){
            perror("StatCheck");
            ExitProcess(-1);

        }

        if(S_ISREG(buf.st_mode)){
            if(strcmp("sortDir.exe",dr->d_name) != 0){
                adaugaFisier(dr->d_name);
                int i;
                i=ultimaAparitie(dr->d_name,'.');
                adaugaExtensie(dr->d_name+i);

            }

        }

    }

    if(closedir(dir) < 0){
        perror("CloseDirCheck");
        ExitProcess(-1);

    }

}

///Functia listare
//Listeaza fisierele si extensiile din liste.
void listare(){
    fisier *auxF;
    extensie *auxE;

    printf("Fisierele continute sunt:");
    for(auxF=rootF;auxF!=NULL;auxF=auxF->urm){

        printf("%s   ",auxF->nume);

    }

    printf("\n\n");
    printf("Extensiile obtinute:");
    for(auxE=rootE;auxE!=NULL;auxE=auxE->urm){

        printf("%s   ",auxE->nume);

    }

    printf("\n\n\n");
}


///Functia creeazaDirectoare.
//Aceasta functie creeaza directoarele specifice extensiilor.
void creeazaDirectoare(char *cale){
    char comanda[PATH];

    char *auxiliar;
    extensie *auxE;

    for(auxE=rootE;auxE!=NULL;auxE=auxE->urm){
        auxiliar=strtok(auxE->nume,".");
        comanda[0]='\0';
        strcat(comanda,"/c mkdir ");
        strcat(comanda,"\"");
        strcat(comanda,cale);
        strcat(comanda,"\\");
        strcat(comanda,auxiliar);
        strcat(comanda,"\"");
        forkk(CMD,comanda);

    }

    printf("\n");
}

///Functia mutaFisiere.
//Aceasta functie muta un fisier in directorul cu extensia specifica fisierului.
void mutaFisiere(char *cale){


    fisier *auxF;
    extensie *auxE;
    char cale1[PATH];
    char cale2[PATH];
    char *folder;

    for(auxF=rootF;auxF!=NULL;auxF=auxF->urm){
        for(auxE=rootE;auxE!=NULL;auxE=auxE->urm){

            if(strstr(auxF->nume,auxE->nume)){

                folder=strtok(auxE->nume,".");
                cale1[0]='\0';
                cale2[0]='\0';
                strcat(cale1,cale);
                strcat(cale1,"\\");
                strcat(cale1,auxF->nume);

                strcat(cale2,cale);
                strcat(cale2,"\\");
                strcat(cale2,folder);
                strcat(cale2,"\\");
                strcat(cale2,auxF->nume);
                if(rename(cale1,cale2) < 0){
                    if(errno == EEXIST){
                        printf("%s-->",auxF->nume);
                        printf("File exists in both directories!\n");
                        continue;

                    }
                    printf("%s:",auxF->nume);
                    perror("MoveFilesRenameCheck");

                }

            }

        }

    }


}

int main(int argc, char* argv[]){
    char path[PATH];
    printf("Sort-Path:");
    gets(path);
    if(stringCheck(path) == 1){
        return 1;
    }

    preluareDate(path);

    creeazaDirectoare(path);

    mutaFisiere(path);

    return 0;
}
