#include "Fibonacci.h"

unsigned long long f;

void init(unsigned long long v[]){
for(int i=0;i<=93;i++)
     v[i]=-1;

}

unsigned long long fibonacci(int n){
    if(n < 0){
        printf("Invalid value!\n\n");
        return 4;

    }

    if(n > 93){
        printf("Overflow!\n\n");
        return 4;

    }

    if(values[n]!=-1)
        return values[n];

    if(n<=2){
        if(n)
            f=1;

        else
            f=0;
    }
    else f=fibonacci(n-1)+fibonacci(n-2);

    values[n]=f;
    return f;

}

void printFibonacci(){
    int n;
    unsigned long long result;
    printf("N:");scanf("%d",&n);
    result = fibonacci(n);
    if(result == 4){
        return;

    }
    printf("Result:%I64u\n\n",result);

}