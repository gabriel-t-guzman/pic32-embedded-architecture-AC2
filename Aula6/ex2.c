#include <detpic32.h>

void delay(unsigned int ms)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000 * ms);    
    }

int main(void)
{
    TRISDbits.TRISD11 = 0; // saida digitla
    TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RB4 configured as analog input
    //n sei que faz
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1;//tamben n sei // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; //IDK Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 0; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
// This must the last command of the A/D
// configuration sequence
    volatile int aux;

    while(1)
    {            
        AD1CON1bits.ASAM = 1;
        resetCoreTimer();
        
        while( IFS1bits.AD1IF == 0);
        
        aux = readCoreTimer();
        int dummy = ADC1BUF0;
        putChar('\r');
        printInt(aux, 10 | 3 << 16);

        delay(3000);

        IFS1bits.AD1IF = 0;
    }
    return 0;
}
