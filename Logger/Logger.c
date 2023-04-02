#include "Logger.h"

PCSTR getDayA(WORD dayOfWeekCode){
	switch(dayOfWeekCode)
	{
		case 0:  return "Sunday";
		case 1:  return "Monday";
		case 2:  return "Tuesday";
		case 3:  return "Wednesday";
		case 4:  return "Thursday";
		case 5:  return "Friday";
		case 6:  return "Saturday";
	}
	return "";
}

PCWSTR getDayW(WORD dayOfWeekCode){
	switch(dayOfWeekCode)
	{
		case 0:  return L"Sunday";
		case 1:  return L"Monday";
		case 2:  return L"Tuesday";
		case 3:  return L"Wednesday";
		case 4:  return L"Thursday";
		case 5:  return L"Friday";
		case 6:  return L"Saturday";
	}
	return L"";
}

PCSTR getMonthA(WORD monthCode){
	switch(monthCode)
	{
		case 1:  return "January";
		case 2:  return "February";
		case 3:  return "March";
		case 4:  return "April";
		case 5:  return "April";
		case 6:  return "June";
		case 7:  return "July";
		case 8:  return "August";
		case 9:  return "September";
		case 10:  return "October";
		case 11:  return "November";
		case 12:  return "December";
	}
	return "";
}

PCWSTR getMonthW(WORD monthCode){
	switch(monthCode)
	{
		case 1:  return L"January";
		case 2:  return L"February";
		case 3:  return L"March";
		case 4:  return L"April";
		case 5:  return L"April";
		case 6:  return L"June";
		case 7:  return L"July";
		case 8:  return L"August";
		case 9:  return L"September";
		case 10:  return L"October";
		case 11:  return L"November";
		case 12:  return L"December";
	}
	return L"";
}

void prepareLogFile()
{
	DWORD error = 0;
    HANDLE logFileHandler = NULL;
    if((logFileHandler = CreateFileW(L"log.txt", 0, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        printf("PrepareLogFileCreateFileAError:%lu\n",error);
        return;

    }

    if(CloseHandle(logFileHandler) == FALSE){
        error = GetLastError();
        printf("CreateFileCloseHandleError%lu\n",error);
        return;

    }

	LogA("mados", __FILE__, INFOA, "Log file created succesfully!");
}

void LogA(PCSTR component, PCSTR file, PCSTR logType, PCSTR text)
{
	FILE* logFile;
    if(fopen_s(&logFile, "log.txt", "a") != 0){
	    if(errno == ENOENT){
	        printf("Log file doesn't exist!\n\n");
	        return;

	    }

	    if(errno == EACCES){
	        printf("Log file is a directory or access is denied!\n\n");
	        return;

	    }

	    printf("PrepareLogFileWfopen_sError:%d\n\n",errno);
	    return;

	}

	if(logFile){
		SYSTEMTIME localTime;
		GetLocalTime(&localTime);

		char month[10];
		char day[10];
		strcpy_s(month, sizeof(month), getMonthA(localTime.wMonth));
		strcpy_s(day, sizeof(day), getDayA(localTime.wDayOfWeek));


		fprintf_s(logFile, "[%s]: %s %hu %s %hu %hu:%hu:%hu.%hu [%s][%s]: %s\n", component, day, localTime.wDay, month, localTime.wYear, localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds, file, logType, text);

		fclose(logFile);
	}
}

void LogW(PCWSTR component, PCWSTR file, PCWSTR logType, PCWSTR text)
{
	FILE* logFile;
    if(_wfopen_s(&logFile, L"log.txt", L"a") != 0){
	    if(errno == ENOENT){
	        printf("Log file doesn't exist!\n\n");
	        return;

	    }

	    if(errno == EACCES){
	        printf("Log file is a directory or access is denied!\n\n");
	        return;

	    }

	    printf("PrepareLogFileWfopen_sError:%d\n\n",errno);
	    return;

	}

	if(logFile){
		SYSTEMTIME localTime;
		GetLocalTime(&localTime);

		WCHAR month[10];
		WCHAR day[10];
		wcscpy_s(month, sizeof(month), getMonthW(localTime.wMonth));
		wcscpy_s(day, sizeof(day), getDayW(localTime.wDayOfWeek));


		fwprintf_s(logFile, L"[%ls]: %ls %hu %ls %hu %hu:%hu:%hu.%hu [%ls][%ls]: %ls\n", component, day, localTime.wDay, month, localTime.wYear, localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds, file, logType, text);

		fclose(logFile);
	}
}
