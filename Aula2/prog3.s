    .iequ READ_CORE_TIMER,11
    .equ RESET_CORE_TIMER,12
    .equ PUT_CHAR,3 # $a0 poe o character
    .equ PRINT_INT,6
    .data
    .text
    .globl main

main: 
      addiu $sp,$sp,-16
      
      sw $ra,0($sp)
      sw $s0,4($sp)
      sw $s1,8($sp)
      sw $s2,12($sp)

      li $s0,0       # $s0 = counter = 0    

while: # while (1) {

      li $v0,PUT_CHAR # putChar('\r')
      li $a0,'\r' 
      syscall
# CABOU A PAUSA
      li $v0,PRINT_INT
      move $a0,$s0  # $a0 = counter
      li $a1,0x0004000A       
      syscall       #  printInt(counter, 10 | 4 << 16)
# 
      li $a0,1
      jal delay

      li $v0,PUT_CHAR # putChar('\r')
      li $a0,'\r' 
      syscall
  
      li $v0,PRINT_INT
      move $a0,$s1  # $a0 = counter
      li $a1,0x0004000A       
      syscall       #  printInt(counter, 10 | 4 << 16)
# 
      li $a0,10
      jal delay


      li $v0,PUT_CHAR # putChar('\r')
      li $a0,'\r' 
      syscall

      li $v0,PRINT_INT
      move $a0,$s2  # $a0 = counter
      li $a1,0x0004000A       
      syscall       #  printInt(counter, 10 | 4 << 16)
# 
      li $a0,1000
      jal delay

      li $v0,RESET_CORE_TIMER #
      syscall # resetCoreTimer()
# 
     

while2:
      li $v0,READ_CORE_TIMER
      syscall
      blt $v0,200000,while2   # while (readCoreTimer() < 200000)
      
      addi $s0,$s0,1  # counter++
      addi $s1,$s1,1
      addi $s2,$s2,1
  
      j while # 


      lw $ra,0($sp)
      lw $s0,4($sp)
      lw $s1,8($sp)
      lw $s2,12($sp)
      addiu $sp,$sp,16

      li $v0,0
      jr $ra

delay:

      li $v0,RESET_CORE_TIMER
      syscall   # reset_coretimer()
      # $a0 e' uma constante 
      li $t1,20000  # ms -> segundos t = $t1 = ms (em segundos)
      mul $t1,$t1,$a0   # $t1 = k * ms

sub_while:

      li $v0,READ_CORE_TIMER
      syscall 
      blt $v0,$t1,sub_while # while (readCoretimer() < K * ms) 

      jr $ra
