.data
nl: .asciiz "\n"
.text
.globl __start

#Imprime un \n à l'ecran
printnl:
la $a0,nl
li $v0,4
syscall
j $ra

#Affiche l'entier dans $a0 à l'ecran
writeln:
li $v0,1
syscall
la $a0,nl
li $v0,4
syscall
j $ra

#Lit un entier a l'entrée standard et le met dans $a0
readint:
li $v0,5
syscall
move $a0,$v0
j $ra




__start:

jal writeln

li $a0,12
jal writeln


jal readint
jal writeln

li $v0,10
syscall
