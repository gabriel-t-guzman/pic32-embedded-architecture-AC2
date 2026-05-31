    .data
    .equ UP,1
    .equ DOWN,0
    .equ RESTART,2
    .equ STOP,3
    .equ PutChar,3 # 
    .equ PrintInt,6 # $a0 <- val $a1 <- base
    .equ Inkey,1
    .text
    .globl main

# TABELA DE REGISTOS
# $s0 = STATE
# $s1 = cnt = 0
# $s2 = c char

main:

    addi $sp,$sp,-16
    sw   $ra,0($sp)
    sw   $s0,4($sp)
    sw   $s1,8($sp)
    sw   $s2,12($sp)

    li $s0,UP # $s0 = STATE = UP
    li $s1,0   # $s1 cnt = 0
        

do:

    li $v0,PutChar 
    li $a0,'\r'
    syscall     # putchar('\r')

    li $v0,PrintInt
    move $a0,$s1 # move
    li $a1,3 # 3 digitos
    sll $a1,$a1,16 # los movemos
    ori $a1,$a1,10  # base 10
    syscall 

    li $v0,PutChar
    li $a0,'\t'
    syscall     # putchar('\t')

    li $v0,PrintInt
    or $a0,$s1,$0 # move
    li $a1,8 # 3 digitos
    sll $a1,$a1,16 # los movemos
    ori $a1,$a1,2  # base 2
    syscall     

    li $a0,10 # 10 1 segundo   
    jal wait # SUBRUTINA ############
       
    li $v0,Inkey
    syscall

    move $s2,$v0  # move

if: bne $s2,'+',elseif 
    li $s0,UP  
    j endif  
elseif: bne $s2,'-',elseif2
    li $s0,DOWN
    j endif
elseif2: bne $s2,'R',elseif3
    li $s0,RESTART
    j endif
elseif3: bne $s2, 's', endif
    li $s0,STOP 
endif:






if2: bne $s0,UP,elsif2 # if(state == UP)
    addi $s1,$s1,1 # cnt ++
    andi $s1,$s1,0xFF    
elsif2: bne $s0,DOWN,elsif3
    addi $s1,$s1,-1
    andi $s1,$s1,0xFF
elsif3: bne $s0,RESTART,else
    li $s1,0
else:
    
    


while: bne $s2,'q',do # while(c != 'q')

 

    lw   $ra,0($sp)
    lw   $s0,4($sp)
    lw   $s1,8($sp)
    lw   $s2,12($sp)
    addi $sp,$sp,16
  
    li $v0,0  # return 0   
    jr $ra 





############
wait:
    li $t0,0
    li $t1,515000
    mul $t1,$a0,$t1 # 515000 * ts    

for: bgt $t0,$t1,endfor # for(i < 515000 * ts)

    addi $t0,$t0,1  # i++
    j for
endfor:
    jr $ra
