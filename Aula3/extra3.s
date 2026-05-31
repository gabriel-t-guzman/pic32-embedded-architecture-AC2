    .data
    .equ  HIGH,0xBF88
    .equ  TRISB,6040
    .equ  PORTB,6050
    .equ  LATB,6060
    .equ  TRISE,6100
    .equ  PORTE,6110
    .equ  LATE,6120
    


    .text
    .globl main



main:

    lui $t0,HIGH  # colocando el high en 0x____XXXX
    lw  $t1,TRISB($t0)
    ori $t1,$t1,0x9  # colocando a (1) port 0 e 3 como entrada
    sw $t1,TRISB($t0) # save

    lw $t1,TRISE($t0)
    andi $t1,$t1,0xFFD4   # colocado a (0) saida os bits 5 e 2
    sw $t1,TRISE($t0)

while:

    lw $t1, LATSB($t0)

    

    j while





    li $v0,0
    jr $ra


