#include "FileOperations.h"

void chooseFileOperation(wchar_t* absolutePath,char* control){
    if(strcmp(control,"cdir") == 0){
        createDirectory(absolutePath);
        return;

    }

    if(strcmp(control,"chdir") == 0){
        createHiddenDirectory(absolutePath);
        return;

    }

    if(strcmp(control,"rdir") == 0){
        removeDirectory(absolutePath);
        return;

    }

    if(strcmp(control,"Rdir") == 0){
        removeDirectoryRecursive(absolutePath, L"R");
        return;

    }

    if(strcmp(control,"cfile") == 0){
        createFile(absolutePath, FILE_ATTRIBUTE_NORMAL);
        return;

    }

    if(strcmp(control,"chfile") == 0){
        createFile(absolutePath, FILE_ATTRIBUTE_HIDDEN);
        return;

    }

    if(strcmp(control,"rfile") == 0){
        removeFile(absolutePath);
        return;

    }

    if(strcmp(control,"hide") == 0){
        setFileProperties(absolutePath, "hide");
        return;

    }

    if(strcmp(control,"show") == 0){
        setFileProperties(absolutePath, "show");
        return;

    }

}

void fileOperationWraper(wchar_t* path, char* control){
    wchar_t filePath[MAX_PATH];
    fgetws(filePath,MAX_PATH,stdin);
    if(filePath[wcslen(filePath)-1] == '\n'){
        filePath[wcslen(filePath)-1] = '\0';
    }

    if(wStringCheck(filePath) == 1){
        return;

    }

    wchar_t* absolutePath;
    if((absolutePath = preparePathDependingOnType(path,filePath)) == NULL){
        return;

    }

    chooseFileOperation(absolutePath,control);

    if(heapFreeChecker(processHeap,0,absolutePath) == FALSE){
        return;

    }

}

BOOL createDirectory(wchar_t* absolutePath){
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return FALSE;

    }

    DWORD error = 0;
    if(CreateDirectoryW(absolutePath,NULL) == 0){
        error = GetLastError();
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return FALSE;

        }

        if(error == ERROR_ALREADY_EXISTS){
            printf("The file already exists!\n");
            return FALSE;

        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return FALSE;

        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Permission denied!\n");
            return FALSE;

        }

        if(error == ERROR_FILENAME_EXCED_RANGE){
            printf("File name is too long!\n");
            return FALSE;

        }

        printf("CreateDirectoryCreateDirectoryError:%lu\n",error);
        return FALSE;

    }

    return TRUE;
}

void createHiddenDirectory(wchar_t* absolutePath){
    if(!createDirectory(absolutePath)){
        return;

    }

    setFileProperties(absolutePath, "hide");

}

int removeDirectory(wchar_t* absolutePath){
    DWORD error = 0;
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return -1;

    }

    if(RemoveDirectoryW(absolutePath) == 0){
        error = GetLastError();

        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return error ;

        }

        if(error == ERROR_DIR_NOT_EMPTY){
            printf("The directory is not empty!\n");
            return error ;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("This path doesn't exist as file!\n");
            return error;
        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return error;

        }

        if(error == ERROR_ACCESS_DENIED){
            printf("You don't have permission to delete this directory!\n");
            return error;

        }

        if(error == ERROR_DIRECTORY){
            printf("The arguments is a regular file, not a directory!\n");
            return error;

        }

        if(error == ERROR_FILENAME_EXCED_RANGE){
            printf("File name is too long!\n");
            return error;

        }

        printf("RemoveDirectoryRemoveDirectoryError:%lu\n",error);
        return error;

    }

    return 0;
}

void removeDirectoryRecursive(wchar_t* absolutePath, PWCHAR control){
    if(wcslen(absolutePath) > 247){
        printf("File name is too long!\n");
        return;

    }

    int pathCheck = 0;
    if((pathCheck=wExist(absolutePath,L"")) == 0){
        printf("This path doesn't exist as file!\n");
        return;

    }

    if(pathCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(pathCheck != 2){
        printf("This path isn't a directory!\n");
        return;

    }


    printf("\nList of deleted files:\n");
    parse(absolutePath, control, NULL, INVALID_HANDLE_VALUE);
    printf("\n");
    if(removeDirectory(absolutePath) == 0){
        printf("The directory was deleted successfully!\n");

    }

}

void createFile(wchar_t* absolutePath, unsigned int fileVisibility){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    DWORD error = 0;
    HANDLE createFileHandler = NULL;
    if((createFileHandler = CreateFileW(absolutePath, GENERIC_WRITE, 0, NULL,CREATE_NEW, fileVisibility, NULL)) == INVALID_HANDLE_VALUE){
        error = GetLastError();
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument or file name is too long!\n");
            return;

        }

        if(error == 80){
            printf("The file exists.\n");
            return;

        }
        if(error == 3){
            printf("A component from argument doesn't exist or file name is too long!\n");
            return;

        }
        if(error == 5){
            printf("Path is a directory or access is denied!\n");
            return;
        }
        printf("CreateFileCreateFileAError:%lu\n",error);
        return;

    }

    if(CloseHandle(createFileHandler) == FALSE){
        error = GetLastError();
        printf("CreateFileCloseHandleError%lu\n",error);
        return;

    }

}

DWORD removeFile(wchar_t* absolutePath){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return 1;

   }

    DWORD error = 0;
    if(DeleteFileW(absolutePath) == 0){
        error = GetLastError();

        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return error;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("This path doesn't exist as file!\n");
            return error;
        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return error;
        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Path is a directory or access is denied!\n");
            return error;
        }

        printf("RemoveFileDeleteFileError:%lu\n",error);
        return error;

    }

    return 0;
}

void renameFileWraper(wchar_t* path){
    wchar_t oldName[MAX_PATH];
    printf("OldName:");
    fgetws(oldName,MAX_PATH,stdin);
    if(oldName[wcslen(oldName)-1] == '\n'){
        oldName[wcslen(oldName)-1] = '\0';

    }

    if(wStringCheck(oldName) == 1){
        return;

    }

    wchar_t* absoluteOldPath;
    if((absoluteOldPath = preparePathDependingOnType(path,oldName)) == NULL){
        return;

    }

    if(wcslen(absoluteOldPath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    int existCheck = 0;
    if((existCheck=wExist(absoluteOldPath,L"")) == 0){
        printf("Old name doesn't exist as file!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    wchar_t newName[MAX_PATH];
    printf("NewName:");
    fgetws(newName,MAX_PATH,stdin);
    if(newName[wcslen(newName)-1] == '\n'){
        newName[wcslen(newName)-1] = '\0';

    }

    if(wStringCheck(newName) == 1){
        return;
    }

    wchar_t* absoluteNewPath;
    if((absoluteNewPath = preparePathDependingOnType(path,newName)) == NULL){
        return;

    }

    if(wcslen(absoluteNewPath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    existCheck = wExist(absoluteNewPath,L"");
    if(existCheck == 1 || existCheck == 2){
        printf("The new name already exists!\n");
        return;

    }

    if(existCheck == 3){
        printf("Invalid argument!\n");
        return;

    }

    renameFile(absoluteOldPath,absoluteNewPath);

    if(heapFreeChecker(processHeap,0,absoluteOldPath) == FALSE){
        return;

    }
    if(heapFreeChecker(processHeap,0,absoluteNewPath) == FALSE){
        return;

    }

}

void renameFile(wchar_t* oldName,wchar_t* newName){
    DWORD error = 0;
    if(MoveFileW(oldName,newName) == 0){
        error = GetLastError();

        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return;

        }

        if(error == ERROR_INVALID_PARAMETER){
            printf("Invalid parameter!\n");
            return;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("Old name doesn't exist as file!\n");
            return;

        }

        if(error == ERROR_ALREADY_EXISTS){
            printf("The new name already exists!\n");
            return;

        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return;
        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Access is denied!\n");
            return;
        }

        if(error == ERROR_SHARING_VIOLATION){
            printf("The process cannot access the file because it is being used by another process!\n");
            return;
        }

        printf("renameFileMoveFileError:%lu\n",error);
        return;

    }

}

BOOL changeFileAttributtes(PDWORD attributes, char* operation){
    if(strcmp(operation,"hide") == 0){
        if((*attributes & 0x02) == 0){
            *attributes += 0x02;
            return TRUE;

        }else{
            printf("File is already invisible!\n\n");
            return FALSE;

        }

    }

    if(strcmp(operation,"show") == 0){
        if((*attributes & 0x02) == 0x02){
            *attributes -= 0x02;
            return TRUE;

        }else{
            printf("File is already visible!\n\n");
            return FALSE;

        }

    }

    printf("Invalid operation!\n");
    return FALSE;

}

void setFileProperties(wchar_t* absolutePath, char* operation){
    if(wcslen(absolutePath) >= MAX_PATH -1){
        printf("File name is too long!\n");
        return;

    }

    DWORD attributes = 0;
    DWORD error = 0;

    if((attributes = GetFileAttributesW(absolutePath)) == INVALID_FILE_ATTRIBUTES){
        error = GetLastError();
        if(error == ERROR_INVALID_NAME){
            printf("Invalid argument!\n");
            return;

        }

        if(error == ERROR_FILE_NOT_FOUND){
            printf("This path doesn't exist as file!\n");
            return;
        }

        if(error == ERROR_PATH_NOT_FOUND){
            printf("A component from argument doesn't exist!\n");
            return;
        }

        if(error == ERROR_ACCESS_DENIED){
            printf("Access is denied!\n");
            return;
        }

        printf("GetFilePropertiesGetFileAttributesWError:%lu\n",error);
        return;

    }

    printf("Current proprieties value: %lu\n", attributes);

    if(changeFileAttributtes(&attributes, operation) == FALSE){
        return;

    }

    if(SetFileAttributesW(absolutePath, attributes) == FALSE){
        error = GetLastError();
        printf("SetFilePropertiesSetFileAttributesWError:%lu\n",error);
        return;

    }

}

void copyFile(wchar_t* sourceAbsolutePath,wchar_t* destinationAbsolutePath){
    DWORD error = 0;
    if(CopyFileW(sourceAbsolutePath,destinationAbsolutePath,TRUE) == FALSE){
        error = GetLastError();
        if(error == 2){
            printf("File doesn't exist!\n");
            return;

        }
        if(error == 3){
            printf("DestinationPath doesn't exist!\n");
            return;

        }
        if(error == 80){
            printf("The file exists.\n\n");
            return;

        }

        printf("CopyFileCheck:%lu\n",error);
        return;

    }
    printf("Regular file was copied successfully!\n\n");

}

void copyDirectoryWraper(wchar_t* path,char* control){
    wchar_t sourcePath[MAX_PATH];
    printf("SourceDirectory:");
    fgetws(sourcePath,MAX_PATH,stdin);
    if(sourcePath[wcslen(sourcePath)-1] == '\n'){
        sourcePath[wcslen(sourcePath)-1] = '\0';

    }

    if(wStringCheck(sourcePath) == 1){
        return;

    }

    wchar_t* absoluteSourcePath;
    if((absoluteSourcePath = preparePathDependingOnType(path,sourcePath)) == NULL){
        return;

    }

    if(wcslen(absoluteSourcePath) > 247){
        printf("File name is too long!\n");
        return;

   }

    int existCheck = 0;
    if((existCheck=wExist(absoluteSourcePath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck == 0){
        printf("SourcePath doesn't exist as file!\n");
        return;

    }

    if(existCheck != 2){
        printf("SourcePath isn't a directory!\n");
        return;

    }

    wchar_t destinationPath[MAX_PATH];
    printf("DestinationDirectory:");

    fgetws(destinationPath,MAX_PATH,stdin);
    if(destinationPath[wcslen(destinationPath)-1] == '\n'){
        destinationPath[wcslen(destinationPath)-1] = '\0';

    }

    if(wStringCheck(destinationPath) == 1){
        return;

    }

    wchar_t* absoluteDestinationPath;
    if((absoluteDestinationPath = preparePathDependingOnType(path,destinationPath)) == NULL){
        return;

    }

    if(wcslen(absoluteDestinationPath) > 247){
        printf("File name is too long!\n\n");
        return;

   }

    if((existCheck=wExist(absoluteDestinationPath,L"")) == 3){
        printf("Invalid argument!\n");
        return;

    }

    if(existCheck != 0){
        printf("The file already exists!\n");
        return;

    }

    copyDirectory(absoluteSourcePath,absoluteDestinationPath);

    if(strcmp(control,"cut") == 0){
        removeDirectoryRecursive(absoluteSourcePath, L"R");

    }

    if(heapFreeChecker(processHeap,0,absoluteSourcePath) == FALSE){
        return;

    }

    if(heapFreeChecker(processHeap,0,absoluteDestinationPath) == FALSE){
        return;

    }

}

void copyDirectory(wchar_t* sourcePath,wchar_t* destinationPath){
    sourcePath[wcslen(sourcePath) + 1] = '\0';
    destinationPath[wcslen(destinationPath) + 1] = '\0';

    SHFILEOPSTRUCTW s = {0};
    s.pFrom = sourcePath;
    s.pTo = destinationPath;
    s.wFunc = FO_COPY;

    int error = 0;
    if((error = SHFileOperationW(&s)) != 0){
        if(error == 2 || error == 124){
            printf("Source directory doesn't exist!\n\n");
            return;

        }
        if(error == 1223){
            printf("Operation was cancelled!\n\n");
            return;

        }

        printf("Error:%d\n",error);
        return;

    }

    printf("Directory was copied successfully!\n\n");

}

HANDLE getFileHandleWrapper(PWCHAR currentPath)
{
    wchar_t filePath[MAX_PATH];
    printf("Output:");
    fgetws(filePath, MAX_PATH, stdin);
    if(filePath[wcslen(filePath)-1] == '\n'){
        filePath[wcslen(filePath)-1] = '\0';
    }

    if(wStringCheck(filePath) == 1){
        return INVALID_HANDLE_VALUE;

    }

    PWCHAR fileAbsolutePath;
    if((fileAbsolutePath = preparePathDependingOnType(currentPath, filePath)) == NULL){
        return INVALID_HANDLE_VALUE;

    }
    if(wcslen(fileAbsolutePath) > 247){
        printf("File name is too long!\n");
        return INVALID_HANDLE_VALUE;

    }

    HANDLE fileHandle = getFileHandle(fileAbsolutePath);

    if(heapFreeChecker(processHeap,0, fileAbsolutePath) == FALSE){
        ExitProcess(-1);

    }

    return fileHandle;
}

HANDLE getFileHandle(PWCHAR fileAbsolutePath)
{
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
    saAttr.bInheritHandle = TRUE; 
    saAttr.lpSecurityDescriptor = NULL; 
    
    HANDLE fileHandle = NULL;
    DWORD error = 0;
    if((fileHandle = CreateFileW(fileAbsolutePath,
                                GENERIC_WRITE,
                                0,
                                &saAttr,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL)) 
    == INVALID_HANDLE_VALUE)
    {
        error = GetLastError();
        if(error == 2){
            printf("The system cannot find the file specified.\n");

        }
        else if(error == 3){
            printf("A part from source path isn't a directory!\n");

        }
        else if(error == 5){
            printf("Source is a directory or access is denied!\n");

        }
        else if(error == 123){
            printf("SourceFilePath is invalid!\n");

        }
        else{
            printf("GetFileHandleCreateFileWRead:%lu\n",error);
            ExitProcess(error);
        }
    }

    return fileHandle;
}

void closeHandle(HANDLE handle)
{
    DWORD error = ERROR_SUCCESS;
    if(CloseHandle(handle) == FALSE){
        error = GetLastError();
        printf("CloseHandleError%lu\n",error);
    }
}
