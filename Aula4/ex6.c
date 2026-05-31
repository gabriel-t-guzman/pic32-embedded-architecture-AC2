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

    LATDbits.LATD5 = 1; // ligado 
    LATDbits.LATD6 = 0;  // desligado 

    while(1)
    {
        int i;
        for (i = 0; i < 7; i++){
          //  char ch = 'a' + i;
            LATB = (LATB & 0x80FF) | 1 << (i + 8);        
            delay(500);
        }
    LATDbits.LATD6 = !LATDbits.LATD6;
    LATDbits.LATD5 = !LATDbits.LATD5;
        
    }
    return 0;
}
