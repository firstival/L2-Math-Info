.data
nl: .asciiz "\n"
.text
.globl __start

__start:

#Lecture d'un entier a
li $v0,5
syscall
move $t1,$v0

#lecture d'un entier b
li $v0,5
syscall
move $t2,$v0


add $t3,$t1,$t2 #c = a + b

# On imprime c à l'ecran
li $v0,1
move $a0,$t3
syscall

# On affiche un \n
li $v0,4
la $a0,nl
syscall

#sortie propre
li $v0,10
syscall
