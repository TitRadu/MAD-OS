#include "UrlRunner.h"

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
    wcscpy_s(url,sizeof(url),L"https://www.imdb.com/search/title/?title=");
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
    wcscpy_s(url,sizeof(url),L"https://www.youtube.com/results?search_query=");
    wcscat_s(url,sizeof(url),searched);

    connectToURL(url);
}