#include <detpic32.h>

void delay(unsigned int ms)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000*ms);
    }


int main(void)
{

    TRISB = TRISB & 0x80FF; // Fica como saida os portos 14-8
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1)
    {
        char ch = getChar();
        if(ch == 'a') LATB = (LATB & 0x80FF) | (1 << 8);
        if(ch == 'b') LATB = (LATB & 0x80FF) | (1 << 9);
        if(ch == 'c') LATB = (LATB & 0x80FF) | (1 << 10);
        if(ch == 'd') LATB = (LATB & 0x80FF) | (1 << 11);
        if(ch == 'e') LATB = (LATB & 0x80FF) | (1 << 12);
        if(ch == 'f') LATB = (LATB & 0x80FF) | (1 << 13);
        if(ch == 'g') LATB = (LATB & 0x80FF) | (1 << 14);
    
    delay(1000);
    
    }
    return 0;
}
