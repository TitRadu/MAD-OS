#ifndef BLUETOOTHOPERATIONS_H_INCLUDED
#define BLUETOOTHOPERATIONS_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include <bluetoothapis.h>
#include "..\..\..\..\Macros.h"

void enumerateBluetoothRadios();
void printBluetoothDeviceInformations(BLUETOOTH_DEVICE_INFO);
void enumerateBluetoothDevices();

#endif // BLUETOOTHOPERATIONS_H_INCLUDED
