#ifndef BACKUP_H_INCLUDED
#define BACKUP_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\..\Helpers/GeneralHelper/GeneralHelper.h"
#include "..\..\..\Helpers/WcharHelper/WcharHelper.h"
#include "..\..\Navigator\Navigator.h"
#include "..\..\Operations\FileOperations\FileOperations.h"

void backupWraper(wchar_t*);
void backup(wchar_t*);

#endif // BACKUP_H_INCLUDED
