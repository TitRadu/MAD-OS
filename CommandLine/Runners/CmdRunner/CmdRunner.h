#ifndef CMDRUNNER_H_INCLUDED
#define CMDRUNNER_H_INCLUDED
#include <stdio.h>
#include <Windows.h>
#include "..\..\Operations\ProcessOperations\ProcessOperations.h"
#include "..\..\ConfigurationInfo.h"
#include "..\..\..\Logger\Logger.h"

#define CMD_COMMAND_NOT_CONFIGURED "Error in CMD directly related commands configuration.\n\
Check if COMSPEC system environment variable contains CMD absolute path.\n\n"

void initializeCmdCommandsConfigurationInfo();
void cmdRunnerWrapper(BOOL, BOOL);
void cmdRunner(PWCHAR, BOOL);

#endif // CMDRUNNER_H_INCLUDED