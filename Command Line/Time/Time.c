#include "Time.h"

void displayTime(){
    time_t t = 0;
    if((t = time(NULL)) == ((time_t)-1)){
        printf("Time error0!\n");
        return;

    }

    char* date;
    if((date = ctime(&t)) == NULL){
        printf("Time error1!\n");
        return;

    }
    date[strlen(date) - 1] = '\0';

    if((date = ctime(&t)) == NULL){
        printf("Time error2!\n");
        return;

    }

    printf("%s\n",date);

}

void timerUp(){
    ULONGLONG startTime = 0;
    ULONGLONG currentTime = 0;
    ULONGLONG timerTime = 0;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    char oneDigitSeconds[2];
    char oneDigitMinutes[2];
    char oneDigitHours[2];

    startTime = GetTickCount64();
    while(1){
        currentTime = GetTickCount64();

        timerTime = currentTime-startTime;
        seconds = (timerTime/1000) % 60;
        minutes = (timerTime / 60000) % 60;
        hours = timerTime / 3600000;

        if (hours < 10) {
            oneDigitHours[0] = '0';
            oneDigitHours[1] = '\0';

        } else {
            oneDigitHours[0] = '\0';
        }

        if (minutes < 10) {
            oneDigitMinutes[0] = '0';
            oneDigitMinutes[1] = '\0';

        } else {
            oneDigitMinutes[0] = '\0';

        }

        if (seconds < 10) {
            oneDigitSeconds[0] = '0';
            oneDigitSeconds[1] = '\0';

        } else {
            oneDigitSeconds[0] = '\0';

        }

        printf("\r%s%d:%s%d:%s%d",oneDigitHours,hours,oneDigitMinutes,minutes,oneDigitSeconds,seconds);
        if(GetKeyState('S') & 0x8000)
        {
            printf("\n");
            break;
        }
    }
}

void timerDown(){
    int timerTimeValueInSeconds;
    ULONGLONG startTime;
    ULONGLONG currentTime;
    UINT remainingTimerTime;

    printf("Counter time:");
    scanf("%d",&timerTimeValueInSeconds);

    startTime = GetTickCount64();
    while(1){
        currentTime = GetTickCount64();

        remainingTimerTime = (timerTimeValueInSeconds) - ((currentTime - startTime)/1000);

        if(remainingTimerTime == 0){

            printf("\rCountdown:0\n");
            while(1){
                Beep(750, 1000);
                if(GetKeyState('S') & 0x8000)
                {
                    printf("\n");
                    break;
                }

            }

        }

        if(GetKeyState('S') & 0x8000)
        {
            printf("\n");
            break;
        }

        printf("\rCountdown:%u ",remainingTimerTime);

    }

}


void activeTime(){
    ULONGLONG activeTime;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    char oneDigitSeconds[2];
    char oneDigitMinutes[2];
    char oneDigitHours[2];


    activeTime = GetTickCount64();
    seconds = (activeTime/1000) % 60;
    minutes = (activeTime / 60000) % 60;
    hours = activeTime / 3600000;

    if (hours < 10) {
        oneDigitHours[0] = '0';
        oneDigitHours[1] = '\0';

    } else {
        oneDigitHours[0] = '\0';
    }

    if (minutes < 10) {
        oneDigitMinutes[0] = '0';
        oneDigitMinutes[1] = '\0';

    } else {
        oneDigitMinutes[0] = '\0';

    }

    if (seconds < 10) {
        oneDigitSeconds[0] = '0';
        oneDigitSeconds[1] = '\0';

    } else {
        oneDigitSeconds[0] = '\0';

    }

    printf("%s%d:%s%d:%s%d\n",oneDigitHours,hours,oneDigitMinutes,minutes,oneDigitSeconds,seconds);

}