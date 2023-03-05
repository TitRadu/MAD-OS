#include "UcharHelper.h"

size_t ucslen(const UCHAR* ustring)
{
    int length = 0;
    while(ustring[length] != '\0')
    {
        length++;
    }

    return length;
}

int ucscmp(const UCHAR* string1, const UCHAR* string2)
{
    if(ucslen(string1) != ucslen(string2))
    {
        return 1;
    }

    for(int i = 0; i < ucslen(string1); i++)
    {
        if(string1[i] != string2[i])
        {
            return 1;
        }
    }

    return 0;
}

int uAllSpaces(const UCHAR* string){
    for(int i = 0;i < ucslen(string);i++){
        if(string[i] != 32){
            return 0;

        }
    }

    return 1;
}

int uStringCheck(const UCHAR* string){
    if(ucscmp(string, (UCHAR*)"") == 0 || uAllSpaces(string) == 1){
        printf("Argument is empty or contains only spaces!\n");
        return 1;

    }

    return 0;

}

UCHAR* fgetus(UCHAR* str,  int numChars, FILE* stream)
{
    char auxStr[numChars];
    fgets(auxStr, numChars, stream);

    for(int i = 0; i <= strlen(auxStr); i++)
    {
        str[i] = auxStr[i];
    }

    return str;
}