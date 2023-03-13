#ifndef WLANOPERATIONS_H_INCLUDED
#define WLANOPERATIONS_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include <wlanapi.h>
#include "..\..\..\..\GlobalVariables.h"
#include "..\..\..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\..\..\Helpers\GeneralHelper\GeneralHelper.h"
#include "..\..\..\..\Helpers\UcharHelper\UcharHelper.h"

void enumWlanInterfaces();
GUID* obtainGUIDFromStringWraper();
GUID* obtainGUIDFromString(wchar_t*);
void sendGUIDAsParameter(char*);
void enumAvaibleNetworks(GUID*);
void disconnectWlanInterface(GUID*);
PWLAN_AVAILABLE_NETWORK getNetworkProprierties(HANDLE, GUID*, UCHAR*, LPCWSTR);
void connectWlanInterfaceWraper();
void connectWlanInterface(GUID*, DOT11_SSID, LPCWSTR);

#endif // WLANOPERATIONS_H_INCLUDED
