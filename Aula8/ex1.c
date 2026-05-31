#include <detpic32.h>


int main(void){

    // configure timer T3 (2Hz with interrupts disabled)
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 39062; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0; // Clear timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence
    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts
    IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag
    
    while(1){
        // wait while T3IF = 0
        while(IFS0bits.T3IF == 0);
     // Reset T3IF
        IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag
    
        putChar('.');
    

    }
    return 0;
}
