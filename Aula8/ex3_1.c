#include <detpic32.h>

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer() < ms*20000);
}

int main(void){
    // configure TRIS ports
    TRISEbits.TRISE0 = 0; // conf as output
    TRISDbits.TRISD8 = 1; // conf as input

 //   PORTDbits.RD0 = 0;// inicia a 0, may be aint needed
//    IEC0bits.INT1IE = 1;
    INTCONbits.INT1EP = 0;
    IFS0bits.INT1IF = 0;
    //   EnableInterrupts();

    LATEbits.LATE0 = 0;
    while(1){ // start program    
        while(IFS0bits.INT1IF == 1){
           LATEbits.LATE0 = 1;
           delay(3000);
           IFS0bits.INT1IF = 0;
           LATEbits.LATE0 = 0;
        }
    }

    return 0;
}

