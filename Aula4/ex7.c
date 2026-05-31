#include <detpic32.h>

void delay(unsigned int ms)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000*ms);
    }


int main(void)
{

    int disp7codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    
    TRISB = (TRISB & 0x80FF) | 0x000F; // Fica como saida os portos 14-8, 3-0 como entrada
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;  // configurados como saida

    LATD = (LATD & 0xFFEF) | 0x0020; //  bit 6 -> 0, bit 5 -> 1 
   // LATDbits.LATD5 = 0;
   /// LATDbits.LATD6 = 1;
    while(1)
    {
        int dips = PORTB & 0x000F;
        int code = disp7codes[dips]; 
        LATB =  code <<  8;        
        delay(500);
        
        
        LATD = (LATD ^ 0x0060);
            
    }
    return 0;
}
