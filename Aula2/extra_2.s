    .data
    .equ Inkey,1
    .equ CONST,20000
    .equ readCoreTimer,11   # return $v0
    .equ resetCoreTimer,12
    .equ putChar,3
    .equ printInt,6
    .text
    .globl main


# $t0 = counter
main:
    addiu $sp,$sp,-16
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)

    li $s0,0   # cnt1 = 0
    li $s1,0    # cnt2 = 0
    li $s2,0    # cnt3 = 0
    li $t2,100
    li $t3,2
    li $t4,10
    
while:
  #### PRINTS
    li $v0,putChar # prepara
    li $a0,'\r'    
    syscall    

    li $v0,printInt
    move $a0, $s0  # print(counter 0)
    li $a1,4
    sll $a1,$a1,16
    ori $a1,$a1,10   # base 10, 4 digitos
    syscall

    li $v0,putChar # prepara
    li $a0,'\t'    
    syscall    

    li $v0,printInt
    move $a0, $s1  # print(counter 1 )
    li $a1,4
    sll $a1,$a1,16
    ori $a1,$a1,10   # base 10, 4 digitos
    syscall

    li $v0,putChar # prepara
    li $a0,'\t'    
    syscall    

    li $v0,printInt
    move $a0, $s2  # print(counter 2 )
    li $a1,4
    sll $a1,$a1,16
    ori $a1,$a1,10   # base 10, 4 digitos
    syscall
############
# INKEY
    li $v0,Inkey
    syscall
    
iff: bne $v0,'A',elsiff
    li $t2,50
    li $t3,2
    li $t4,10
elsiff: bne $v0,'N',endiff
    li $t2,100
endiff:

############
    move $a0,$t2  # 200 milisegundos = 0.2 sec
    jal delay

    addi $s0,$s0,1 # cnt1++
    move $t1,$t3
    rem $t0,$s0,$t1
    

if1: bgt $t0,$0,if2
    addi $s1,$s1,1 #cnt5++

if2: move $t1,$t4
    rem $t0,$s0,$t1
     bgt $t0,$0,continue
    addi $s2,$s2,1 # cnt10 ++

continue:

    j while
   
    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    lw $s2,12($sp)
    addiu $sp,$sp,16

     
    jr $ra 


#######



delay: 
    
    li $v0,resetCoreTimer
    syscall
    li $t0,CONST
    mul $a0,$t0,$a0

while_delay:
    li $v0,readCoreTimer
    syscall
    
   
    blt $v0,$a0,while_delay # 

    jr $ra   # saimos do delay


