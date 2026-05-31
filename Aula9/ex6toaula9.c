#include <detpic32.h>

volatile int voltage = 0; // global variable
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

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;// inicia conversao
    IFS0bits.T1IF = 0; //reset flag
}

void _int_(12) isr_T3(void){
    send2displays(voltage);// send to display
    IFS0bits.T3IF = 0; // reset flag;
}

void _int_(27) isr_adr(void){
    putChar('\r');
    int *p = (int *)(&ADC1BUF0);
    int soma = 0;
    int j;
    for( j = 0; j < 4; j++ ) {
        putChar('\t');
        printInt( p[j*4], 10 | 4 << 16 );
        soma += p[j*4]; 
    }
    int media = soma/4;
    voltage = (unsigned char)((media * 33 + 511)/1023);
    putChar('\r');
    printInt(voltage, 10 | 2 << 16); 
    IFS1bits.AD1IF = 0; // reset flag 0
}


void configureAll(void){

    TRISDbits.TRISD5 = 0; //saida
    TRISDbits.TRISD6 = 0; //saida

    TRISB = TRISB & 0x80FF; // output bits dispay7
 
    TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
    AD1PCFGbits.PCFG4= 0; //RB4 configured as analog  input                    
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1;//Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; //IDK Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 3; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    // INTERRUPT T1
    T1CONbits.TCKPS = 2; // 2:64
    PR1 = 62499; // PR1
    TMR1 = 0; // set do counter do T1
    IPC1bits.T1IP = 2; // priridad
    IEC0bits.T1IE = 1; // enable do interrupt
    IFS0bits.T1IF = 0; // flag a 0
    // INTERRUPT T3
    T3CONbits.TCKPS = 2; // 2:4
    PR3 = 49999; // PR1
    TMR3 = 0; // set do counter do T3
    IPC3bits.T3IP = 2; // priridad
    IEC0bits.T3IE = 1; // enable do interrupt
    IFS0bits.T3IF = 0; // flag a 0
    // INterrupt AD1 
    IPC6bits.AD1IP = 2; // priotiti
    IEC1bits.AD1IE = 1; // liga o enable
    IFS1bits.AD1IF = 0; // flag 1 0

    T3CONbits.ON = 1; // inicia a contagem
    T1CONbits.ON = 1; // inicia a contagem
    AD1CON1bits.ON = 1; // Enable A/D converter
// This must the last command of the A/D
}

    

int main(void)
{
    configureAll();
    EnableInterrupts();
    while(1){
        IdleMode();
    }
    return 0;
}
