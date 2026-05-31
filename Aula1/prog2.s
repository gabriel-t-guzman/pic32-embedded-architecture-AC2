    .equ PRINT_STR,8
    .data
    .text
    .globl main

#getChar() $v0 = 2. retorno em $v0  
#putChar() $v0 = 3   entrada em $a0
# $t0 = cnt
# $t1 = c (char)
main: 
      li $t0,0  # $t0 = cnt = 0

do: 
      li $v0,2 # prepara o syscall    
      syscall
      move $t1,$v0  # $t1 = c = getChar()
      
      li $v0,3  # preparar o sycall 
      move $a0,$t1 
      syscall # putChar(c)

      addi $t0,$t0,1  # cnt++
      
      
while: 
      bne  $t1,'\n',do  # while (c != '\n')

      li $v0,6  # prepara PrintInt
      move $a0,$t0
      li $a1,10
      syscall


      li $v0,0      
      jr $ra    # return 0


