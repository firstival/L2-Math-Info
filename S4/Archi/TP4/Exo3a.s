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

jal readint #Recuperation de a
move $t0,$a0
move $t2,$t0#Copie de a dans tmp

jal readint#Recuperation de b
move $t1,$a0


loop:
beq $t1,$zero, exit		#si b==0 alors arret du programme
move $a0,$t2 	#Affichage de tmp
jal writeln
add $t2,$t2,$t0		#tmp=tmp+a
addi $t1,$t1,-1 	#b--
j loop #On continue de boucler


#sortie propre
exit:
li $v0,10
syscall
