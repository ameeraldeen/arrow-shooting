#include "../Base/Includes.h"


void delay(int seconds)
{
    int miSeconds = 1000 * seconds;
    clock_t startTime = clock();
    while (clock() < startTime + miSeconds);
}