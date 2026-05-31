    .equ READ_CORE_TIMER,11
    .equ RESET_CORE_TIMER,12
    .equ PUT_CHAR,3 # $a0 poe o character
    .equ PRINT_INT,6
    .data
    .text
    .globl main

main: 

      li $t0,0       # $t1 = counter = 0    

while: # while (1) {

      li $v0,PUT_CHAR # putChar('\r')
      li $a0,'\r' 
      syscall


      li $v0,PRINT_INT
      move $a0,$t0  # $a0 = counter
      li $a1,0x0004000A#       
      syscall       #  printInt(counter, 10 | 4 << 16)

      li $v0,RESET_CORE_TIMER #
      syscall # resetCoreTimer()

while2:
      li $v0,READ_CORE_TIMER
      syscall
      blt $v0,200000,while2   # while (readCoreTimer() < 200000)
      
      addiu $t0,$t0,1  # counter++
      j while # 

      li $v0,0


      jr $ra
