#include <detpic32.h>

void delay(unsigned int  ms){
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void putc(char byte2send){
// wait while UTXBF == 1 (UxSTA register)
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte2send;
// Copy byte2send to the UxTXREG register
}

void putstr(char *string){
    while(*string){
        putc(*string);
        string++;
    }
}


char getc(void){
    if (U2STAbits.OERR == 1) U2STAbits.OERR = 0;
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}

int main(void){

// Configure UART2:
// 1 - Configure BaudRate Generator
    int baudrate = 115200;
    U2BRG = ((PBCLK+8*baudrate)/(16*baudrate))-1;
    U2MODEbits.BRGH = 0; // 1:4//0:16
// 2 – Configure number of data bits, parity and number of stop bits
// (see U2MODE register)
    U2MODEbits.PDSEL = 0; // 8 bits non parity
    U2MODEbits.STSEL = 0; // 1 bit stop
// 3 – Enable the trasmitter and receiver modules (see register U2STA)
 //   U2STASET = 0x1400;
    U2STAbits.UTXEN = 1; // Ativa o transmisor
    U2STAbits.URXEN = 1; // Ativa o receitor
// 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;
    
    while(1){
    
        putstr("VIADO QUEM LEIA ");
        delay(1000);       
    
    
    }
    return 0;
}
