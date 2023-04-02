#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include <shlwapi.h>
#include "..\..\..\Helpers\WcharHelper\WcharHelper.h"
#include "..\..\Operations\FileOperations\FileOperations.h"
#include "..\..\Runners\InternalRunner\InternalRunner.h"
#include "..\..\Navigator\Navigator.h"
#include "..\..\..\Helpers\GeneralHelper\GeneralHelper.h"
#include "..\..\Runners\GeneralRunner\GeneralRunner.h"
#include "..\..\ConfigurationInfo.h"
#include "..\..\..\Logger\Logger.h"

void setPathDirectoryConfigurationState();
void createPathDirectory();
void initializePathDirectory();
void pathCommandSelector(PCHAR, PWCHAR);
void listPathDirectory();
void addFileInPathDirectory(PWCHAR);
void removeFileFromPathDirectory();
void removePathDirectory();
void runFileFromPathDirectory(BOOL);

#endif // PATH_H_INCLUDED
