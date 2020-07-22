#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <direct.h>
#include <errno.h>
#include <time.h>
#include <Windows.h>
#define PATH 1024

void pause(){
    printf("Press enter or any key+enter to continue...\n");
    getchar();

}

void parse(char* path,char control,int* numberOfFiles,int* numberOfDirectories){
    DIR* dir = NULL;
    if((dir=opendir(path)) == NULL){
        perror("OpendirCheck");
        ExitProcess(-1);
    }

    char newpath[2*PATH];
    struct dirent* dr = NULL;
    while((dr=readdir(dir)) !=NULL){
        if((strcmp(dr->d_name,".") == 0) || (strcmp(dr->d_name,"..") == 0)){
            continue;

        }

        if(control == 'r' || control == 'R'){
            snprintf(newpath,PATH,"%s\\%s",path,dr->d_name);

        }else{
            snprintf(newpath,PATH,"%s\%s",path,dr->d_name);

        }

        struct _stat st;
        if(_stat(newpath,&st) < 0){
            if(strlen(newpath) > 260){
                (*numberOfFiles)++;
                printf("File:%s\n",newpath);
                continue;

            }

            perror("parseExistStatCheck");
            printf("File:%s\n",newpath);
            pause();
            ExitProcess(-1);

        }

        float sizeMB = 0;
        sizeMB = (float)st.st_size/((float)1024*(float)1024);

        char* modified;
        if((modified = ctime(&st.st_mtime)) == NULL){
            printf("Time error!\n");
            return;

        }
        modified[strlen(modified) - 1] = '\0';

        if(S_ISREG(st.st_mode)){
            (*numberOfFiles)++;

            if(control == 'R')
                if(unlink(newpath) < 0){
                    perror("parseExistUnlinkCheck");
                    ExitProcess(-1);

                }
                printf("F\t%.3f\t\t%s\t%s\n",sizeMB,modified,newpath);

        }

        if(S_ISDIR(st.st_mode)){
            (*numberOfDirectories)++;

            if(control == 'r' || control == 'R'){
                parse(newpath,control,numberOfFiles,numberOfDirectories);
                if(control == 'R')
                if(_rmdir(newpath) < 0){
                    perror("parseExistRmdirCheck");
                    ExitProcess(-1);

                }

            }
            printf("D\t%.3f\t\t%s\t%s\n",sizeMB,modified,newpath);

        }

    }

}

int main(int argc,char* argv[]){
    SetConsoleCtrlHandler(NULL,FALSE);
    int numberOfFiles = 0;
    int numberOfDirectories = 0;
    printf("Type\tSize(MB)\tModified\t\t\tPath\n");
    parse(argv[1],argv[2][0],&numberOfFiles,&numberOfDirectories);
    printf("Directory statistics: Files:%d   Directories:%d\n",numberOfFiles,numberOfDirectories);

    return 0;
}


