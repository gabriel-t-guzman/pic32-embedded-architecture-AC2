#include <detpic32.h>                                              

// Interrupt Handler
void _int_(27) isr_adc(void) // 27 é o vetor correto para o ADC
{
    // 1. Ler o resultado e imprimir (já está pronto, não precisamos de 'while')
    printInt(ADC1BUF0, 16 | 3 << 16);
    putChar('\r');

    // 2. Dar a ordem para iniciar a PRÓXIMA conversão
    AD1CON1bits.ASAM = 1; 

    // 3. Baixar a flag para não ficarmos presos na interrupção
    IFS1bits.AD1IF = 0; 
}

int main(void){//x=4
    TRISBbits.TRISB4 = 1; //Desativacao do output digital (por ativacao do input digital ne?)
    AD1PCFGbits.PCFG4= 0; //Ativacao do input analogico
    AD1CON1bits.SSRC = 7;  // modo 7, conversao automatica
    AD1CON1bits.CLRASAM = 1; // lmpia el bit ASAM que da incio a la conversion, y para de convertir cuando el falg es 1
    AD1CON3bits.SAMC = 16; // tiempo de conversion 16 TAD
    AD1CON2bits.SMPI = 0; // CAntidad de samples
    AD1CHSbits.CH0SA = 4; // Numero del input channel N=4 (Este caso)
    AD1CON1bits.ON = 1; // Activa el convertidor

    // --- NOVA CONFIGURAÇÃO DE INTERRUPÇÕES ---
    IPC6bits.AD1IP = 2; // Configura a prioridade da interrupção do ADC (1 a 7)
    IFS1bits.AD1IF = 0; // Limpa a flag por precaução antes de ativar
    IEC1bits.AD1IE = 1; // Ativa (Enable) a interrupção específica do ADC

    EnableInterrupts(); // Global Interrupt Enable

    // --- FAÍSCA INICIAL ---
    // Start da 1ª A/D conversion para a roda começar a girar
    AD1CON1bits.ASAM = 1; 
e
    while(1)
    {
        // O processador fica aqui a "descansar" (ou a fazer outras coisas)
        // Quando o ADC termina a conversão, salta automaticamente para a isr_adc
    }
    
    return 0;
}
