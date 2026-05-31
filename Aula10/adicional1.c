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

void getstr(char *str, int max_len){
    int i = 0;
    for (; i<max_len; i++){
        char aux_c = getc();
        if (aux_c == '\n') {
            str[i] = aux_c;
            i++;
            break;
        }
        str[i] = aux_c;
        putc(aux_c);
    }
    str[i] = '\0';
}
void configureUart2(unsigned int baud, char parity, unsigned int stopbits){
// Configure UART2:
// 1 - Configure BaudRate Generator
    U2BRG = ((PBCLK+8*baud)/(16*baud))-1;
    U2MODEbits.BRGH = 0; // 1:4//0:16
// 2 – Configure number of data bits, parity and number of stop bits
// (see U2MODE register)
    int aux = 0;
    if (parity == 'N') aux = 0;
    if (parity == 'O') aux = 2;
    if (parity == 'E') aux = 1;
    U2MODEbits.PDSEL = aux; // 8 bits non parity

    stopbits = stopbits - 1;
    U2MODEbits.STSEL = stopbits; // 1 bit stop
                          
// 3 – Enable the trasmitter and receiver modules (see register U2STA)
 //   U2STASET = 0x1400;
    U2STAbits.UTXEN = 1; // Ativa o transmisor
    U2STAbits.URXEN = 1; // Ativa o receitor
// 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;
}


int main(void){

    configureUart2(115200,'N',1);
    TRISE = TRISE & 0xFF00;  // config to output
    LATE = LATE & 0xFF00;
    int i = 0;
    char p_str[3];
    char aux_n = 0;
    while(1){

        getstr(p_str,3);
            aux_n = p_str[1];
            aux_n = aux_n - '0';
        if (p_str[0] == 'L'){
            LATE = (LATE | (1 << (aux_n)));

        } else if (p_str[0] == 'D'){
            LATE = (LATE & ~(1 << (aux_n)));
        } else if (p_str[0] == 'S'){
            aux_n = (LATE & 0x00FF);
            putc('\n');
            char aux_c = 0;
            for (i = 0; i<8;i++){ 
                aux_c = ((aux_n >> (7-i)) & 1) + '0';
                putc(aux_c);
            }
        }

        putc('\n');
        delay(1000);
        
    }
    return 0;
}
