#include <detpic32.h>

volatile unsigned char cnt;
volatile unsigned char SW;
volatile unsigned char STOP;

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
 
void _int_(8) isr_T2(void) // Replace VECTOR by the timer T2
// vector number
{
    // Reset T3 interrupt flag
    send2displays(cnt); 
    SW = PORTBbits.RB0;
    STOP = PORTBbits.RB3;
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag
}

void _int_(4) isr_T1(void) // Replace VECTOR by the timer T3
// vector number
{
    static int c = 1;
    if (c==2){
        if (STOP == 0){
            if (SW == 1 ) cnt = (cnt + 1 )%30; //ascendente
            else cnt = (cnt + 29)%30; // descendente
        }
        c = 0;
    }
    c++;
    // Reset T1 interrupt flag
     IFS0bits.T1IF = 0; // Reset timer T2 interrupt flag
}


int main(void){

    
    TRISD = TRISD & 0xFF9F; //1001enable displays
    TRISB = TRISB & 0x80FF; //0110 enable bits dos displays
    TRISB = TRISB | 0x0009; // 1001 configura 3 e 0 a '1' input 
   // configure timer T2 (2Hz with interrupts disabled)
    T2CONbits.TCKPS = 2; // 1:4 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = 49999; // Fout = 100Hz / (32 * (62499 + 1)) = 10 Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence
    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag
 
/////////////
    // configure timer T1 ( with interrupts disabled)
    T1CONbits.TCKPS = 3; // 1:256 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 39061; // Fout = 1Hz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0; // Clear timer T1 count register
    T1CONbits.TON = 1; // Enable timer T1 (must be the last command of the
    // timer configuration sequence
    IPC1bits.T1IP = 3; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T1 interrupts
    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag
    
    EnableInterrupts();

    while(1){
        // wait while T3IF = 0
       // while(IFS0bits.T3IF == 0);
     // Reset T3IF
    IdleMode();
            
    }
    return 0;
}
