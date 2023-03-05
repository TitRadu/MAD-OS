#include "WlanOperations.h"

void enumWlanInterfaces(){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    PWLAN_INTERFACE_INFO_LIST pwlanInterfaceInfoList = NULL;
    PWLAN_INTERFACE_INFO pwlanInterfaceInfo = NULL;
    wchar_t stringGUID[40] = {0};
    DWORD error = 0;



    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("EnumWlanInterfacesWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanEnumInterfaces(wlanHandle, NULL, &pwlanInterfaceInfoList)) != ERROR_SUCCESS){
        printf("EnumWlanInterfacesWlanEnumInterfacesError:%lu",error);
        ExitProcess(error);

    }else{
        wprintf(L"Number of interfaces: %lu\n\n", pwlanInterfaceInfoList->dwNumberOfItems);
        for(int i = 0; i < (int)pwlanInterfaceInfoList->dwNumberOfItems; i++){
            pwlanInterfaceInfo = &pwlanInterfaceInfoList->InterfaceInfo[i];
            wprintf(L" Interface index:%lu\n",i);
            error = StringFromGUID2(&pwlanInterfaceInfo->InterfaceGuid, (LPOLESTR) &stringGUID, 39);
            if(error == 0 ){
                wprintf(L"EnumWirelessInterfacesStringFromGUID2Error!");
                ExitProcess(-1);

            }else{
                wprintf(L" Interface GUID: %ls\n", stringGUID);

            }
            wprintf(L" Interface description: %ls\n", pwlanInterfaceInfo->strInterfaceDescription);
            wprintf(L" Interface state:\t");
            switch (pwlanInterfaceInfo->isState) {
            case wlan_interface_state_not_ready:
                wprintf(L"Not ready\n");
                break;
            case wlan_interface_state_connected:
                wprintf(L"Connected\n");
                break;
            case wlan_interface_state_ad_hoc_network_formed:
                wprintf(L"First node in a ad hoc network\n");
                break;
            case wlan_interface_state_disconnecting:
                wprintf(L"Disconnecting\n");
                break;
            case wlan_interface_state_disconnected:
                wprintf(L"Not connected\n");
                break;
            case wlan_interface_state_associating:
                wprintf(L"Attempting to associate with a network\n");
                break;
            case wlan_interface_state_discovering:
                wprintf(L"Auto configuration is discovering settings for the network\n");
                break;
            case wlan_interface_state_authenticating:
                wprintf(L"In process of authenticating\n");
                break;
            default:
                wprintf(L"Unknown state %ld\n", pwlanInterfaceInfo->isState);
                break;
            }
            wprintf(L"\n");

        }

    }

    if (pwlanInterfaceInfoList != NULL) {
        WlanFreeMemory(pwlanInterfaceInfoList);
        pwlanInterfaceInfo = NULL;

    }

    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("EnumWlanInterfacesWlanCloseHandleError:%lu",error);
        ExitProcess(error);

    }

}

GUID* obtainGUIDFromStringWraper(){
    wchar_t stringGUID[40] = {0};
    printf("GUID:");
    fgetws(stringGUID,40,stdin);
    if(stringGUID[wcslen(stringGUID)-1] == '\n'){
        stringGUID[wcslen(stringGUID)-1] = '\0';

    }

    return obtainGUIDFromString(stringGUID);

}

GUID* obtainGUIDFromString(wchar_t* stringGUID){
    if(wStringCheck(stringGUID) == 1){
        return NULL;

    }

    LPCLSID clsid;
    if((clsid = (LPCLSID)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(CLSID))) == NULL){
        printf("ObtainGUIDFromStringHeapAllocError!\n");
        ExitProcess(-1);

    }

    if(CLSIDFromString((LPCOLESTR) stringGUID, clsid) == E_INVALIDARG){
        printf("ObtainGUIDFromStringCLSIDFromStringError\n");
        ExitProcess(-1);

    }
    return (GUID*) clsid;

}

void sendGUIDAsParameter(char* control){
    GUID* guid;
    if((guid = obtainGUIDFromStringWraper()) == NULL){
        return;

    }

    if(strcmp(control, "networks") == 0){
        enumAvaibleNetworks(guid);

    }

    if(strcmp(control, "disconnect") == 0){
        disconnectWlanInterface(guid);

    }

    if(heapFreeChecker(processHeap,0,guid) == FALSE){
        return;

    }

}


void enumAvaibleNetworks(GUID* guid){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    PWLAN_AVAILABLE_NETWORK_LIST pwlanAvaibleNewtworkList = NULL;
    PWLAN_AVAILABLE_NETWORK pwlanAvaibleNetwork = NULL;
    int semnalQuality;
    DWORD error = 0;

    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("EnumAvaibleNetworksWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanGetAvailableNetworkList(wlanHandle, guid, 3, NULL, &pwlanAvaibleNewtworkList)) !=  ERROR_SUCCESS){

        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return;
        }
        printf("EnumAvaibleNetworksWlanGetAvaibleNetworkListError:%lu",error);
        ExitProcess(error);

    }else{
        wprintf(L"Number of networks: %lu\n\n", pwlanAvaibleNewtworkList->dwNumberOfItems);

        for(int i = 0; i < pwlanAvaibleNewtworkList->dwNumberOfItems; i++){
            pwlanAvaibleNetwork = &pwlanAvaibleNewtworkList->Network[i];
            if(pwlanAvaibleNetwork->dot11Ssid.uSSIDLength == 0){
                wprintf(L"SSID:None\n");

            }else{
                wprintf(L"SSID[%d]:",i);
                for(int j = 0; j < pwlanAvaibleNetwork->dot11Ssid.uSSIDLength; j++){
                    wprintf(L"%c",pwlanAvaibleNetwork->dot11Ssid.ucSSID[j]);


                }
                wprintf(L"\n");
                wprintf(L"Profile: %ls\n", pwlanAvaibleNetwork->strProfileName);
                wprintf(L"Security Enabled[%d]:\t ", i);
                if (pwlanAvaibleNetwork->bSecurityEnabled){
                    wprintf(L"Yes\n");

                }else{
                    wprintf(L"No\n");

                }
                 if (pwlanAvaibleNetwork->wlanSignalQuality == 0){
                    semnalQuality = -100;
                } else if (pwlanAvaibleNetwork->wlanSignalQuality == 100){
                    semnalQuality = -50;
                } else{
                    semnalQuality = -100 + (pwlanAvaibleNetwork->wlanSignalQuality/2);
                }

                wprintf(L"Signal Quality[%d]:\t %d (RSSI Strength: %d dBm)\n", i,
                    pwlanAvaibleNetwork->wlanSignalQuality, semnalQuality);

                wprintf(L"Connectable[%d]:\t ", i);
                if (pwlanAvaibleNetwork->bNetworkConnectable){
                    wprintf(L"Yes\n");
                }else {
                    wprintf(L"No\n");

                }
                printf("BSS:%d\n",pwlanAvaibleNetwork->dot11BssType);


            }
            wprintf(L"\n");

        }

    }

    if (pwlanAvaibleNewtworkList != NULL) {
        WlanFreeMemory(pwlanAvaibleNewtworkList);
        pwlanAvaibleNewtworkList = NULL;
    }

    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("EnumAvaibleNetworksWlanCloseHandleError:%lu",error);
        ExitProcess(error);

    }

}

void disconnectWlanInterface(GUID* guid){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    DWORD error = 0;

    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("DisconnectWlanInterfaceWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanDisconnect(wlanHandle, guid, NULL)) !=  ERROR_SUCCESS){

        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return;
        }

        printf("DisconnectWlanInterfaceWlanDisconnectError:%lu",error);
        ExitProcess(error);

    }

    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("DisconnectWlanInterfaceWlanCloseHandleError:%lu",error);
        ExitProcess(error);

    }

}

PWLAN_AVAILABLE_NETWORK getNetworkProprierties(HANDLE wlanHandle, GUID* guid, UCHAR* ssidString, LPCWSTR profile){
    PWLAN_AVAILABLE_NETWORK_LIST pwlanAvaibleNewtworkList = NULL;
    WLAN_AVAILABLE_NETWORK currentAvaibleNetwork;
    PWLAN_AVAILABLE_NETWORK pwlanAvaibleNetwork;
    int networkExist = 0;
    DWORD error = 0;


    if((error = WlanGetAvailableNetworkList(wlanHandle, guid, 3, NULL, &pwlanAvaibleNewtworkList)) !=  ERROR_SUCCESS){
        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return NULL;
        }
        printf("EnumAvaibleNetworksWlanGetAvaibleNetworkListError:%lu",error);
        ExitProcess(error);

    }else{
        for(int i = 0; i < pwlanAvaibleNewtworkList->dwNumberOfItems; i++){
                currentAvaibleNetwork = pwlanAvaibleNewtworkList->Network[i];
                if((currentAvaibleNetwork.strProfileName == NULL) || (wcslen(currentAvaibleNetwork.strProfileName) == 0)){
                    continue;

                }

                UCHAR currentSSID[100];
                for(int j =0; j<pwlanAvaibleNewtworkList->Network[i].dot11Ssid.uSSIDLength; j++){
                    currentSSID[j] = pwlanAvaibleNewtworkList->Network[i].dot11Ssid.ucSSID[j];

                }

                currentSSID[pwlanAvaibleNewtworkList->Network[i].dot11Ssid.uSSIDLength] = '\0';

                if((ucscmp(currentSSID, ssidString) == 0) && (wcscmp(currentAvaibleNetwork.strProfileName, profile) == 0)){
                    if((pwlanAvaibleNetwork = (PWLAN_AVAILABLE_NETWORK)HeapAlloc(processHeap,HEAP_ZERO_MEMORY,sizeof(WLAN_AVAILABLE_NETWORK))) == NULL){
                        printf("GetNetworkPropriertiesHeapAllocError!\n");
                        ExitProcess(-1);

                    }

                    CopyMemory(pwlanAvaibleNetwork, pwlanAvaibleNewtworkList->Network + i, sizeof(WLAN_AVAILABLE_NETWORK));
                    networkExist = 1;
                    break;

            }

        }

    }

    if (pwlanAvaibleNewtworkList != NULL) {
        WlanFreeMemory(pwlanAvaibleNewtworkList);
        pwlanAvaibleNewtworkList = NULL;
    }

    if(!networkExist){
        printf("A network with this parameters doesn't exist!\n\n");
        return NULL;

    }
    return pwlanAvaibleNetwork;

}

void connectWlanInterfaceWraper(){
    GUID* guid = obtainGUIDFromStringWraper();

    DOT11_SSID dot11ssid;
    printf("SSID:");
    fgetus(dot11ssid.ucSSID, WLAN_MAX_NAME_LENGTH, stdin);
    if(dot11ssid.ucSSID[ucslen(dot11ssid.ucSSID)-1] == '\n'){
        dot11ssid.ucSSID[ucslen(dot11ssid.ucSSID)-1] = '\0';

    }
    if(uStringCheck(dot11ssid.ucSSID) == 1){
        return;

    }
    dot11ssid.uSSIDLength = ucslen(dot11ssid.ucSSID);

    wchar_t profile[WLAN_MAX_NAME_LENGTH] = {0};
    printf("Profile:");
    fgetws(profile,WLAN_MAX_NAME_LENGTH,stdin);
    if(profile[wcslen(profile)-1] == '\n'){
        profile[wcslen(profile)-1] = '\0';

    }
    if(wStringCheck(profile) == 1){
        return;

    }

    connectWlanInterface(guid, dot11ssid, profile);

    if(heapFreeChecker(processHeap,0,guid) == FALSE){
        return;

    }

}

void connectWlanInterface(GUID* guid, DOT11_SSID ssid, LPCWSTR profile){
    HANDLE wlanHandle;
    DWORD clientVersion = 1;
    DWORD negotiatedVersion = 0;
    DWORD error = 0;

    if((error = WlanOpenHandle(clientVersion, NULL, &negotiatedVersion, &wlanHandle)) != ERROR_SUCCESS){
        printf("ConnectWlanInterfaceWlanOpenHandleError:%lu",error);
        ExitProcess(error);

    }

    PWLAN_AVAILABLE_NETWORK connectionNetworkData = getNetworkProprierties(wlanHandle, guid, ssid.ucSSID, profile);
    if(connectionNetworkData == NULL){
        return;

    }
    WLAN_CONNECTION_PARAMETERS wlanConnectionParameters;
    wlanConnectionParameters.wlanConnectionMode = wlan_connection_mode_profile;
    //wcscpy_s(wlanConnectionParameters.strProfile, sizeof(wchar_t) * WLAN_MAX_NAME_LENGTH, profile);
    wlanConnectionParameters.strProfile = profile;
    wlanConnectionParameters.pDot11Ssid = &ssid;
    wlanConnectionParameters.pDesiredBssidList = NULL;
    wlanConnectionParameters.dot11BssType = connectionNetworkData->dot11BssType;

    if((error = WlanConnect(wlanHandle, guid, &wlanConnectionParameters, 0)) !=  ERROR_SUCCESS){

        if(error == ERROR_NOT_FOUND){
            printf("Interface not found!\n");
            return;
        }

        printf("ConnectWlanInterfaceWlanDisconnectError:%lu",error);
        ExitProcess(error);

    }


    if((error = WlanCloseHandle(wlanHandle, NULL)) != ERROR_SUCCESS){
        printf("ConnectWlanInterfaceWlanCloseHandleError:%lu\n",error);
        ExitProcess(error);

    }

}