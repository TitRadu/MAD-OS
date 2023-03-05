#include "BluetoothOperations.h"

void enumerateBluetoothRadios(){
    HBLUETOOTH_RADIO_FIND bluetoothRadioFindHandle;
    BLUETOOTH_FIND_RADIO_PARAMS bluetoothFindRadioParams;
    bluetoothFindRadioParams.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);
    HANDLE bluetoothRadioHandle;
    DWORD error = 0;


    if((bluetoothRadioFindHandle = BluetoothFindFirstRadio(&bluetoothFindRadioParams, &bluetoothRadioHandle)) == NULL){
        error = GetLastError();
        if(error == ERROR_NO_MORE_ITEMS){
            return;

        }


        printf("EnumerateBluetoothRadiosBluetoothFindFirstRadioError: %lu\n", error);
        ExitProcess(error);

    }

    BLUETOOTH_RADIO_INFO bluetoothRadioInfo;
    bluetoothRadioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
    if((error =  BluetoothGetRadioInfo(bluetoothRadioHandle, &bluetoothRadioInfo)) != ERROR_SUCCESS){
        printf("EnumerateBluetoothRadiosBluetoothGetRadioInfoError: %lu\n", error);
        ExitProcess(error);

    }

    wprintf(L"Radio name: %ls\n", bluetoothRadioInfo.szName);
    wprintf(L"Manufacturer: %d\n", bluetoothRadioInfo.manufacturer);
    wprintf(L"Adress: %p\n\n", bluetoothRadioInfo.address.ullLong);

    while(1){
        if(BluetoothFindNextRadio(bluetoothRadioFindHandle, bluetoothRadioHandle) == FALSE){
            error = GetLastError();
            if(error == ERROR_NO_MORE_ITEMS){
                return;

            }
            printf("EnumerateBluetoothRadiosBluetoothFindNextRadioError: %lu\n", error);
            ExitProcess(error);

        }

        wprintf(L"Radio name: %ls\n", bluetoothRadioInfo.szName);
        wprintf(L"Manufacturer: %d\n", bluetoothRadioInfo.manufacturer);
        wprintf(L"Adress: %p\n\n", bluetoothRadioInfo.address.ullLong);

    }

    if(CloseHandle(bluetoothRadioHandle) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothRadiosCloseHandleError:%lu\n",error);
        return;

    }

    if(BluetoothFindRadioClose(bluetoothRadioFindHandle) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothRadiosBluetoothFindRadioCloseError:%lu", error);
        ExitProcess(error);

    }

}

void printBluetoothDeviceInformations(BLUETOOTH_DEVICE_INFO deviceInfo){
    DWORD error = 0;
    wprintf(L"Device name: %s\n", deviceInfo.szName);
    if(deviceInfo.fConnected){
        printf("Connected: YES\n");

    }else{
        printf("Connected: NO\n");

    }
    wchar_t localDate[THIRTY];
    if(GetDateFormatEx(NULL, DATE_LONGDATE, &deviceInfo.stLastUsed, NULL, localDate, sizeof(localDate)/sizeof(wchar_t), NULL ) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothDevicesGetDateFormatExError:%lu\n", error);
        ExitProcess(error);

    }
    wprintf(L"%ls ", localDate);
    if(GetTimeFormatEx(NULL, 0, &deviceInfo.stLastUsed, NULL, localDate, sizeof(localDate)/sizeof(wchar_t)) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothDevicesGetTimeFormatExError:%lu\n", error);
        ExitProcess(error);

    }
    wprintf(L"%ls\n\n", localDate);

}

void enumerateBluetoothDevices(){
    HBLUETOOTH_DEVICE_FIND bluetoothDeviceFindHandle;

    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams;
    searchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.fIssueInquiry = TRUE;
    searchParams.cTimeoutMultiplier = 1;
    searchParams.hRadio = NULL;

    BLUETOOTH_DEVICE_INFO deviceInfo;
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    DWORD error = 0;


    if((bluetoothDeviceFindHandle = BluetoothFindFirstDevice(&searchParams,&deviceInfo)) == NULL){
        error = GetLastError();
        if(error == ERROR_NO_MORE_ITEMS){
            return;

        }
        printf("EnumerateBluetoothDevicesBluetoothFindFirstDeviceError:%lu\n", error);
        ExitProcess(error);
    }

    printBluetoothDeviceInformations(deviceInfo);

    while(1){
        if(BluetoothFindNextDevice(bluetoothDeviceFindHandle, &deviceInfo) == FALSE){
        error = GetLastError();
        if(error == ERROR_NO_MORE_ITEMS){
            return;

        }

        printf("EnumerateBluetoothDevicesBluetoothFindNextDeviceError:%lu\n",error);
        ExitProcess(error);

        }

        printBluetoothDeviceInformations(deviceInfo);

    }

    if(BluetoothFindDeviceClose(bluetoothDeviceFindHandle) == FALSE){
        error = GetLastError();
        printf("EnumerateBluetoothDevicesBluetoothFindDeviceCloseError:%lu", error);
        ExitProcess(error);

    }

}