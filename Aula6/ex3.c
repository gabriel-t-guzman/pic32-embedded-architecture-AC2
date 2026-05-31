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


int main(void)
{
    

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0; //saida

    TRISB = TRISB & 0x80FF;
 
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
    AD1CON2bits.SMPI = 3; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
// This must the last command of the A/D
// configuration sequence
    int i = 0;
    int media = 0;
    unsigned char V = 0;
    while(1){
        
    
        if (i % 20 == 0){
            AD1CON1bits.ASAM = 1;
 
            while( IFS1bits.AD1IF == 0);
        
             putChar('\r');
             int *p = (int *)(&ADC1BUF0); // Devemos tratar o resgistro ADC1 como punteroa int para nao leer posicoes erradas ex: 0x9074
             int soma = 0;
             int j;
             for( j = 0; j < 4; j++ ) {
                 putChar('\t');
                 printInt( p[j*4], 10 | 4 << 16 );
                 soma += p[j*4]; // multiplicar x4 pela mesma razao nao somar um registro errado
             
                 
             }
             media = soma/4;
             V = (unsigned char)((media * 9 + 511)/1023);
            putChar('\r');
            printInt(V, 10 | 2 << 16); 
            IFS1bits.AD1IF = 0;
             
        }
                
        

        delay(10);
        i++;
        send2displays(V);
    

    
    }
    return 0;
}
