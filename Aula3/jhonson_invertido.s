     .data    
     .equ READ_CORE_TIMER,11      
     .equ RESET_CORE_TIMER,12
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
 

# ASIGNACAO
# $t0 = ADDR_BASE_HI
# $t1 = v_temporal
# $t2 = counter

 main:

    addiu $sp,$sp,-12   #
    sw $ra,0($sp)   # $ra
    sw $s0,4($sp)   # $s0 = counter
    sw $s1,8($sp)   # $s1 = flag


    lui $t0,ADDR_BASE_HI   # carregando $t0 = 0xBF880000 

    lw $t1,TRISE($t0) # $t0 must be previously initialized
    andi $t1,$t1,0xFFE1 # Reset bits 4-1
    sw $t1,TRISE($t0) # Update TRISE register
    lw $t1,TRISB($t0) # Read TRISB register
    ori $t1,$t1,0x000E # Set bits 
    sw $t1,TRISB($t0) # Update TRISB register

    li $s0,1 # $t2 = Counter = 0

while:
 
    lw $s1,PORTB($t0)  # read de input
    andi $s1,$s1,0x0008 #  1___

    lw $t1,LATE($t0)    # read late register
    andi $t1,$t1,0xFFE1  # Limpa os bits 4-1 do LATE
    sll $t3,$s0,1  # da shitf para o 2* bit (devido a que n pode ir direto, tem que deslocar um bit, o counter esta normal mas o display nao)
    or $t1,$t1,$t3     # merge do counter com o LATE(display)
    sw $t1,LATE($t0)    # write  do merge

    li $a0,666   # 1000 ms = 1 s
    jal delay      # faz o delay

    
### CONTAR

    andi $t2,$s0,0x1  
    sll $t2,$t2,3  # desloca tres espacos
    xor $t2,$t2,0x8   # nega o bit
    
    srl $s0,$s0,1  # deslocamento a esquerda
    or $s0,$s0,$t2 # uniao com o seu bit mais significativo negado


    andi $s0,$s0,0x000F   # MOD 16, so ficam o primerio byte
   

    j while

    # Carregar valores 
    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    addiu $sp,$sp,8

    li $v0,0
    jr $ra    # acaba o programa



###############################
delay:

    li $v0,RESET_CORE_TIMER
    syscall   # reset_coretimer()
    # $a0 e' uma constante 
    li $t1,20000  # ms -> segundos t = $t1 = ms (em segundos)
    mul $t1,$t1,$a0   # $t1 = k * ms

delay_while:
 
    li $v0,READ_CORE_TIMER
    syscall 
    blt $v0,$t1,delay_while # while (readCoretimer() < K * ms) 
    
    jr $ra #  volta para a funcao
    

    

