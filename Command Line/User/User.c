#include "User.h"

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