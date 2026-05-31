#include <detpic32.h>

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer() < (ms * 20000));
}

unsigned char toBcd(unsigned char value){
    return ((value/10) << 4) + (value %10);
}

void send2displays(unsigned char value){

    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; // static variable: doesnt loose  its value betwen cllls to function
    int dl = (toBcd(value)) & 0x0F;
    int dh = ((toBcd(value)) & 0xF0) >> 4 ;

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
    TRISCbits.TRISC14 = 0; // delcarado como saida
    TRISE = TRISE & 0xFF00; //declarar como saida 7-0
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;  // configurando como saida
    TRISB = (TRISB & 0x80FF) | 0x0001; //rb0 entrada  // Por como saida bits do 8 ate o 15
// int disp7codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x7    7, 0x7C, 0x39, 0x5E, 0x79, 0x71};     
    int counter = 0;
    int i = 0;
    while(1){
        
        
        
            send2displays(counter);
            LATE = (LATE & 0xFF00) | (toBcd(counter));
            delay(10);
        i++;
        int i2 = (i)%10;    
        int i3 = (i)%50;    
        int k = PORTBbits.RB0;
        if (k != 0 && i2 == 0){
            counter = (counter + 1) % 60; 
            if (counter == 59) {
                LATCbits.LATC14 = 1;
                delay(5000);
                LATCbits.LATC14 = 0;
            }
        } else if (i3 == 0) {
            counter = (counter + 59) % 60; 
            if (counter == 0) {
                LATCbits.LATC14 = 1;
                delay(5000);
                LATCbits.LATC14 = 0;
            }
        }
    }
}
