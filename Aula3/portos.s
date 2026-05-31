    .data
    .equ ADDR_BASE_HI,0xBF88 # Base address: 16 MSbits
    .equ TRISE,0x6100 # TRISE address is 0xBF886100
    .equ PORTE,0x6110 # PORTE address is 0xBF886110
    .equ LATE,0x6120 # LATE address is 0xBF886120
    .equ TRISB,0x6040
    .equ PORTB,0x6050
    .equ LATB,0x6060
    .equ TRISD,0x60C0
    .equ LATD,0x60E0
    .equ PORTD,0x60D0

    .text

    .globl main

main:

    lui $t0,ADDR_BASE_HI  # $t0 = 0xbf880000
    lw $t1,TRISE($t0)     #  $t1 <- (sube) O valor armazenado em 0xbf880000 + 0x000061000
    andi $t1,$t1,0xFFFE    #  colocando o 1* bit = 0 (saida)
    sw $t1,TRISE($t0)      # guardado

#    lw $t1,TRISB($t0)
 #   andi $t1,$t1,0x0001    # colocando o 1* bit = 1 (entrada)
#    sw $t1,TRISB($t0)    # guardado

    lw $t1,TRISD($t0)
    ori $t1,$t1,0x0100    # colocando o 9* bit = 1 (entrada)
    sw $t1,TRISD($t0)    # guardado

while:
    
#   lw $t1,PORTB($t0) # $t1 <- sube o valor armazenado em 0xbf88000 + 0x00006050
    lw $t1,PORTD($t0) 
   
    srl $t1,$t1,8
    xor $t1,$t1,0x0001
    sw $t1,LATE($t0)    # salva no registo saida de PORT'E'
    

    j while

    li $v0,0
    jr $ra
