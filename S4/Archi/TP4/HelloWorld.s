.data
hw: .asciiz "Hello World\n"

.text
.globl __start


__start :
li $v0,4
la $a0,hw
syscall

li $v0,10
syscall
