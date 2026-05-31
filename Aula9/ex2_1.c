#include <detpic32.h>


void setPWM(unsigned int dutyCycle){
    //duty_cycle must be between [0, 100]
    OC1RS = (dutyCycle*(PR3+1))/100;    
}


void configureAll(void){
//SET led 11 RC14
    TRISCbits.TRISC14 = 0; // conf as output
    
//CONFIGURE T3
    T3CONbits.TCKPS = 2; //2:4 k prescaler
    PR3 = 49999; 
    TMR3 = 0;
    IPC3bits.T3IP = 2; //  prioridade
    IFS0bits.T3IF = 0; // reset flag 0
    IEC0bits.T3IE = 1; //enable do T3;
//configrue OC1
    OC1CONbits.OCM = 6; // PWM mode 6, pin siable and works 
    OC1CONbits.OCTSEL = 1; // use the timer 2 as base for PWM
//    OC1RS = 12500;
    setPWM(20);
    T3CONbits.ON = 1; //  Enable Timer T3;
    OC1CONbits.ON = 1; // Enable OC1 XD
}



int main(void){
    configureAll();

    while(1){
         LATCbits.LATC14 = PORTDbits.RD0;
    }
    return 0;
}
