#include <detpic32.h>                                              

volatile unsigned char voltage = 0;

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer() < 20000*ms);
}

char unsigned toBcd (unsigned char value){
    return ((value/10) << 4) + (value%10);
}

void send2displays (unsigned char value){

    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; // static variable: doesnt loose  its value betwen cllls to function
    int dl = (toBcd(value)) & 0x0F;
    int dh = ((toBcd(value)) & 0xF0) >> 4;

    if (displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dl] << 8);
    } else {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dh] << 8);
    }
    displayFlag = 1 ^ displayFlag;
}

// Interrupt Handler
void _int_(27) isr_adc(void){

    putChar('\r');
    int *p = (int*)(&ADC1BUF0);
    int j;
    int soma = 0;
    for (j=0; j < 8; j++){
        // 1. Ler o resultado e imprimir (já está pronto, não precisamos de 'while')
        putChar('\t');
        printInt(p[j*4], 10 | 4 << 16);
        soma += p[j*4];
    }
        // 2. Dar a ordem para iniciar a PRÓXIMA conversão
    int media = soma/8;
    voltage = (unsigned char)((media*66 +511)/1023);
    putChar('\r');
    voltage = voltage + 7; // TESTAR NA PICA 32
    printInt(voltage, 10 | 4 << 16);
   // 3. Baixar a flag para não ficarmos presos na interrupção
    IFS1bits.AD1IF = 0; 
    
}
int main(void){
    
    TRISB = TRISB & 0x80FF; // set dos portos 14-8 como saida (displays)
    TRISD = TRISD & 0xFF9F; //1001 1111  // enable dos dysplays 
    TRISBbits.TRISB4 = 1; 
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1; 
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = 7; 
    AD1CHSbits.CH0SA = 4; 
    AD1CON1bits.ON = 1; 

    // --- NOVA CONFIGURAÇÃO DE INTERRUPÇÕES ---
    IPC6bits.AD1IP = 2; // Configura a prioridade da interrupção do ADC (1 a 7)
    IFS1bits.AD1IF = 0; // Limpa a flag por precaução antes de ativar
    IEC1bits.AD1IE = 1; // Ativa (Enable) a interrupção específica do ADC

    EnableInterrupts(); // Global Interrupt Enable

    unsigned int cnt = 0;
    // --- FAÍSCA INICIAL ---
    // Start da 1ª A/D conversion para a roda começar a girar

    while(1)    {
        if(cnt == 0) // 0, 200 ms, 400 ms, ... (5 samples/second)
        {
            // Start A/D conversion
            AD1CON1bits.ASAM = 1; 
        }
        // Send "voltage" value to displays
        send2displays((unsigned char)(voltage));
        cnt = (cnt + 1) % 20;//:
           // Wait 10 ms
        delay(10);
    }
    return 0;
}
