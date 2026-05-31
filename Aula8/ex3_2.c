#include <detpic32.h>`
void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer() < ms*20000);
}

volatile unsigned int t2_counter = 0;

// ==========================================
// TIMER 2 ISR (Handles turning the LED OFF)
// ==========================================
void _int_(8) isr_T2(void) {
    t2_counter++;

    if (t2_counter >= 6) { // 6 * 0.5s = 3 seconds reached!
        LATEbits.LATE0 = 0;   // Turn OFF LED
        T2CONbits.TON = 0;    // Turn OFF Timer 2 (stop counting)
        t2_counter = 0;       // Reset software counter
    }

    IFS0bits.T2IF = 0; // CRITICAL: Clear the Timer 2 flag!
}


void _int_(7) isr_INT1(void){

    
    LATEbits.LATE0 = 1;
    T2CONbits.TON = 1;
    IFS0bits.INT1IF = 0; // set IF del INT1 a 0

}


int main(void){
    // configure TRIS ports
    TRISEbits.TRISE0 = 0; // conf as output
    TRISDbits.TRISD8 = 1; // conf as input

    //set INT1
    INTCONbits.INT1EP = 0; // Polaridad
    IPC1bits.INT1IP = 2; // priotidad
    IFS0bits.INT1IF = 0; // set IF del INT1 a 0
    IEC0bits.INT1IE = 1; // ativamos o interrupt enable do botao INT1
   
    //set T2
    T2CONbits.TCKPS = 7;
    PR2 = 29061;
    TMR2 = 0;
    IPC2bits.T2IP = 2; // pririty
    IFS0bits.T2IF = 0; // Flag a 0
    IEC0bits.T2IE = 1; // enable do T2

    EnableInterrupts();

    LATEbits.LATE0 = 0;
    
    while(1){ // start program    
        IdleMode();
    }

    return 0;
}

