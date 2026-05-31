    .data
    .equ CONST,20000000
    .equ readCoreTimer,11   # return $v0
    .equ resetCoreTimer,12
    .equ putChar,3
    .equ printInt,6
    .text
    .globl main


# $t0 = counter
main:

    li $t0,0
while:
    
    li $v0,putChar # prepara
    li $a0,'\r'    
    syscall    

    li $v0,printInt
    move $a0, $t0  # print(counter )
    li $a1,4
    sll $a1,$a1,16
    ori $a1,$a1,10   # base 10, 4 digitos
    syscall

    li $v0,resetCoreTimer
    syscall

while2:
    li $v0,readCoreTimer
    syscall
    
    blt $v0,CONST,while2

    addi $t0,$t0,1 # counter ++

    j while

    jr $ra 




