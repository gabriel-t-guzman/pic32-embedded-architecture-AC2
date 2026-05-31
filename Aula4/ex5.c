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
        if (ch >= 'a' && ch <= 'g'){
            ch = ch - 'a';
            LATB = (LATB & 0x80FF) | 1 << (ch + 8);        
        } 
    delay(10);
    
    }
    return 0;
}
