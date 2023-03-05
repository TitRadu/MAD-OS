#include "BasicCalculator.h"

int characterCheck(char character){
    if(isdigit(character) == 0 && character != '-'  ){
        return 1;

    }

    return 0;

}

int spaceCountCheck(char* string){
    int nr = 0;

    for(int i = 0;i < strlen(string);i++){
        if(string[i] == 32){
            nr++;

        }

    }

    return nr;

}

int allDigits(char* string){
    if(characterCheck(string[0]) == 1){
        return 1;

    }

    for(int i = 1;i < strlen(string);i++){
        if(isdigit(string[i]) == 0){
            return 1;

        }
    }

    return 0;
}

int operatorCheck(char c){
    if (c != '+' && c != '-' && c != '*' && c != '/' && c != '%'){
        return 1;

    }

   return 0;

}

void eval(int operand1,int operation,int operand2){
    switch(operation){
    case '+' : printf("Result:%d\n\n",operand1 + operand2);break;
    case '-' : printf("Result:%d\n\n",operand1 - operand2);break;
    case '*' : printf("Result:%d\n\n",operand1 * operand2);break;
    case '/' : printf("Result:%.3f\n\n",((float)operand1 / (float)operand2));break;
    case '%' : printf("Result:%d\n\n",operand1 % operand2);break;

    }

    return;
}

char* breakString(char* string,char* separators){
    char* breakSt;
    int operand1,operand2;
    int operation;
    int stringLength = 0;
    char auxString[1];
    auxString[0] = '\0';
    strcat(auxString,string);

    if((breakSt = strtok(string,separators)) == NULL){
        return "NoMatch";

    }


    if(allDigits(breakSt) == 1){
        return "NoMatch";

    }

    if(auxString[strlen(breakSt)] != 32){
        return "NoMatch";

    }


    stringLength += strlen(breakSt);
    stringLength += 1;

    operand1 = atoi(breakSt);

    if((breakSt = strtok(NULL,separators)) == NULL){
        return "NoMatch";

    }


    if (strlen(breakSt) > 1){
        return "NoMatch";

    }

    if(operatorCheck(breakSt[0]) == 1){
        return "NoMatch";

    }

    stringLength += strlen(breakSt);
    stringLength += 1;


    if(auxString[stringLength -1] != 32){
        return "NoMatch";

    }

    operation = breakSt[0];

    if((breakSt = strtok(NULL,separators)) == NULL){
        return "NoMatch";

    }

    if(allDigits(breakSt) == 1){
        return "NoMatch";

    }

    operand2 = atoi(breakSt);

    if((breakSt = strtok(NULL,separators)) != NULL){
        return "NoMatch";

    }

    eval(operand1,operation,operand2);
    return "Match";

}


char* compute(char* expression){

    if(characterCheck(expression[0]) == 1){
        return "NoMatch";
    }

    if(spaceCountCheck(expression) > 2){
        return "NoMatch";
    }

    return breakString(expression," ");
}