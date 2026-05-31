#include <detpic32.h>

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer() < (ms * 20000));
}

void send2displays(unsigned char value){

    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; // static variable: doesnt loose  its value betwen cllls to function
    int dl = value & 0x0F;
    int dh = value >> 4;

    // select display high
    // send digit_high (dh) to display
   

    if (displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dl] << 8) ;
    } else {
    LATDbits.LATD6 = 1;
    LATDbits.LATD5 = 0;
    LATB = (LATB & 0x80FF) | (disp7Scodes[dh] << 8);
    }
    displayFlag = 1 ^ displayFlag;
 


}


int main(void){

    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;  // configurando como saida
    TRISB = TRISB & 0x80FF;   // Por como saida bits do 8 ate o 15
// int disp7codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x7    7, 0x7C, 0x39, 0x5E, 0x79, 0x71};     

    while(1){

       send2displays(0x15);

       delay(10);
    
    
    
    
    
    
    }
}
