#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include <lm.h>
#include "..\..\GlobalVariables.h"
#include "..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Helpers\GeneralHelper\GeneralHelper.h"

void statusCheck(NET_API_STATUS,LPDWORD);
void getUserInfoWraper();
void getUserInfo(wchar_t*);
void listUsers();
void listUserLocalGroupsWraper();
void listUserLocalGroups(wchar_t*);
void addUserWraper();
void addUser(wchar_t*,wchar_t*);
void deleteUserWraper();
void deleteUser(wchar_t*);
void changeUserPasswordWraper();
void changeUserPassword(wchar_t*,wchar_t*,wchar_t*);
void getLocalGroupInfoWraper();
void getLocalGroupInfo(wchar_t*);
void listLocalGroups();
void listLocalGroupMembersWraper();
void listLocalGroupMembers(wchar_t*);

#endif // USER_H_INCLUDED
