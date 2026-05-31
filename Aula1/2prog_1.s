    .data
    .equ PutChar,3 # $a0 <- char. 
    .text
    .globl main

# Tabela de asignacoes
# $t0 = cnt
# $t1 = char
main:

    li $t0,0 # $t0 = cnt = 0
do:

    li $v0,2  # GetChar
    syscall
    move $t1,$v0 # MOVE $t1 = GetChar()
    
    li $v0,PutChar   # putchar()
    or $a0,$t1,$0    # preparacao do syscall
    addi $a0,$a0,1
    syscall
 
    addi $t0,$t0,1   # cnt++
  
while:
    bne $t1,'\n',do  # while(c != '\n')

    li $v0,6  # prinInt()
    li $a1,3 # preparando a base
    sll $a1,$a1,16 # mexe 16 bits 4 bytes
    or  $a1,$a1,10
    move $a0,$t0    # carrega o cnt
    syscall

    li $v0,0      # return 0
    jr $ra




