#include <detpic32.h>

void delay(unsigned int ms)
    {
        resetCoreTimer();
        while(readCoreTimer() < 7407407*ms);
    }


int main(void)
{

    TRISE = TRISE & 0xFF87; // saida
    int counter = 0;

    while(1)
    {
    // delay 1 sec
        LATE = (LATE & 0xFF87) | counter << 3;
        delay(1);
        counter = (counter - 1 + 10) % 10; // modulo 10

    }
    return 0;
}
