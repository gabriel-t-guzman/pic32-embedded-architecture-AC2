    .data
    .equ Inkey,1     # return $v0
    .equ PutChar,3   # retorno $v0
    .equ PrintInt,6  # retorno $v0
    .text
    .globl main

#Registos
# $t0 = cnt
# $t1 = char = c
main:

    addi $sp,$sp,-12
    sw $ra,0($sp) # guarda o ra
    sw $s0,4($sp) # para o cnt
    sw $s1,8($sp) # para o char
        

    li $s0,0  # cnt = 0

while:
    
    li $v0,Inkey  # preparando
    syscall    # 
    move $s1,$v0 

if: 
    bne $s1, 'R' , elif    # if(c == 'R')
    li $s0,0      # cnt = 0
    j endif
elif: 
    bne $s1, 's' , endif
    j end #para el programa  
endif:
    li $v0,PutChar
    li $a0,'\r'
    syscall     # putChar('\r')

    li $v0,PrintInt # preparand
    move $a0,$s0
    li $a1,3
    sll $a1,$a1,16
    ori $a1,$a1,10 # printInt(cnt,10 | 3 << 16)
    syscall        

    addi $s0,$s0,1  # cnt ++
    andi $s0,$s0,0xFF

    li $a0,10   # 4segundos
    jal wait


    j while
    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    addi $sp,$sp,12 # limpo

end:
    li $v0,0   # fim
    jr $ra


###### subrutina

wait:
 
    li $t0,0  #i=0
    li $t1,515000
    mul $t1,$a0,$t1 # ts * 515000
for:
   
    addi $t0,$t0,1 #i ++
    blt $t0,$t1,for  # for(i=0; i < ts*515000: i++)
   
    jr $ra
    

    

   
    
    
    


    
    
    

    
