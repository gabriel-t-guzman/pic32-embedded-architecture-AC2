    .equ PRINT_STR,8
    .data
    .text
    .globl main

#inkey() $v0 = 1. retorno em $v0  
#putChar() $v0 = 3   entrada em $a0
#printInt   $a0 = val $a1= base
# $t0 = cnt
# $t1 = c (char)
main: 
      li $t0,0  # $t0 = cnt = 0

while: 
      li $v0,1
      syscall 
      move $t1,$v0   # $t1 = c

if:   
      bne $t1,'R',endif  # if(c == 'R')
      li $t0,0  # $t0 = cnt = 0
endif:
      li $v0,3 
      li $a0,'\r' 
      syscall 

      li $t2,3
      sll $t2,$t2,16
      ori $t2,$t2,10 # $t2 = 10 | 3 << 16

      li $v0,6  # prepara o syscall
      li $a0,$t1
      move $a1,$t2 # base = (10 | 3 << 16)

      addi $t0,$t0,1  # c = c + 1    
  
      andi $t0,$t0,0xFF # cnt = cnt+1 * 0xFF  
    
      li $v0,0      
      jr $ra    # return 0


