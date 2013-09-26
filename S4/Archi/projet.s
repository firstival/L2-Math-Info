#
# PROJET D'ARCHITECTURE DES ORDINATEURS
# KUNTZ THOMAS
#

.data
nb_element: .asciiz "Veuillez rentrer le nombre d'element souhaite pour le tableau\n"
saisi1: .asciiz "Veuillez rentrer le "
saisi2: .asciiz "1er element : "
saisi3: .asciiz "eme element : "
taillenulle: .asciiz "Taille de tableau donné nulle ou négative : Fin du programme\n\n"
tabsaisi: .asciiz "Tableau saisi :\n"
tabtri: .asciiz "Tableau trié :\n"

nouvelle_ligne: .asciiz "\n"
pipe: .asciiz "|"
space: .asciiz " "

.text

.globl __start



#Fonction de saisi d'un entier : met l'entier dans $a0
readInt:
li $v0,5
syscall
move $a0,$v0
jr $ra



#Affiche un \n
printnl:
la $a0,nouvelle_ligne
li $v0,4
syscall
j $ra




#Affiche la demande de taille de tableau
affichageTailleTableau:
li $v0,4
la $a0,nb_element
syscall
j $ra




#Affiche l'entier dans a0
printInt:
li $v0,1
syscall

j $ra



#Affiche l'entier dans a0 puis un pipe
printIntTab:
li $v0,1
syscall

li $v0,4
la $a0,space
syscall

li $v0,4
la $a0,pipe
syscall

li $v0,4
la $a0,space
syscall

j $ra



#Affiche la phrase de saisi du 1er élément
affichageSaisiElement1:
li $v0,4
la $a0,saisi1
syscall

li $v0,4
la $a0,saisi2
syscall

jr $ra





#Affiche la phrase de saisi du ieme élément(i passé par la pile)
affichageSaisiElementi:
li $v0,4
la $a0,saisi1
syscall

li $v0,1
lw $a0,0($sp)
syscall

li $v0,4
la $a0,saisi3
syscall

jr $ra



#Gère une taille négatif ou nulle du tableau
erreurTaille:
li $v0,4
la $a0,taillenulle
syscall
j __exit





#Fonction qui demande la saisi du tableau : a la fin de l'appel, la pile est alloué de n+1 élement, n élément du tableau
#Avec le dernier élément du tableau le plus haut dans la pile, et au sommet de pile la taille du tableau

saisiTableau:

move $t9,$ra #on met $ra dans un registre qu'on ne touchera pas : je ne peux pas le mettre dans la pile car on va ajouter par dessus le tableau

#Saisi de la taille du tableau
jal affichageTailleTableau
jal readInt
move $t0,$a0 # $t0 = n


ble $t0,$zero,erreurTaille #Si la taille est nulle ou négatif, on quitte le programme


#Saisi du 1er élément
jal affichageSaisiElement1
jal readInt
move $t1,$a0

addi $sp,$sp,-4 # Allocation et mise dans la pile du 1er élément du tableau
sw $t1,0($sp)

addi $t2,$zero,2 # t2 contient la valeur de i, et commence à 2 vu qu'on a déjà un élément

li $t5,2
blt $t0,$t1,__finSaisi # Si on n'a qu'un élément à renseigner on jump à finSaisi

loop_saisi:
addi $sp,$sp,-8 # Allocation dans la taille de la place pour le ieme element du tableau, ainsi que pour i qui serra passé en paramètre de 
sw $t2,0($sp) #On met i dans le sommet de pile
jal affichageSaisiElementi #On affiche la demande de saisi en fonction de i
addi $sp,$sp,4 #On enleve i de la pile
jal readInt # On saisi le ieme élément
move $t1,$a0
sw $t1,0($sp) #On met le ieme élément dans le haut de la pile

addi $t2,$t2,1 #i++

ble $t2,$t0,loop_saisi # si i<=n alors on recommence

__finSaisi:

#A ce stade, on a dans la pile tout les élément du tableau, il ne manque que "n" au sommet de la pile

addi $sp,$sp,-4 #Allocation d'un élément dans la pile pour "n"
sw $t0,0($sp)

move $ra,$t9 #On remet la bonne valeur de $ra
j $ra




#fonction qui affiche le tableau : le tableau doit être dans la pile avec la taille du tableau au sommet de la pile
printTab:

addi $sp,$sp,-4
sw $ra,0($sp) #Ajout dans la pile de $ra

#L'adresse du 1er élément du tableau dans la pile est à l'adresse ($sp + 4*(tailleTab+1))
lw $t0,4($sp) # $t0=tailleTableau

li $t1,4
addi $t2,$t0,1
mult $t1,$t2
mflo $t1 
add $t1,$sp,$t1 # t1 vaut l'adresse de la 1er valeur du tableau, t1=($sp + 4*(tailleTab+1))


li $t2,0 # i=0
addi $t3,$t0,-1 # n=tailleTab-1

loop_affichage:
bge $t2,$t3,fin_loop_affichage #Si i>=n alors on sort de la boucle (tant que i<n, on continue)
lw $a0,0($t1) #Le ieme élément est mis dans a0
jal printIntTab # Affichage du ieme élément, avec un espace puis pipe, puis espace
addi $t2,$t2,1 # i++
addi $t1,$t1,-4 #L'adresse du (i+1)ème élément est égal à t1-4

j loop_affichage #On boucle


fin_loop_affichage:

lw $a0,0($t1)
jal printInt # Affichage du dernier élément sans le pipe ni espace

jal printnl # On saute une ligne

lw $ra,0($sp)
addi $sp,$sp,4 # On récupère $ra dans la pile, et on supprime sa place dans la pile

j $ra



#Fonction qui trie le tableau dans la pile : la taille du tableau doit être au sommet de la pile (en dessous le dernier élément du tableau
triTableau:

lw $t0,0($sp)  #t0=tailleTableau
li $t1,0 # i=0
li $t2,0 # j=0

li $t3,4
move $t4,$t0
mult $t3,$t4
mflo $t3 
add $t3,$sp,$t3 # t3 vaut l'adresse de la 1er valeur du tableau, t3=($sp + 4*tailleTab)

#
#
# t3 : pointeur sur l'élément à modifier (Ce qui deviendras le prochain minimum du sous tableau restant)
# t4 : pointeur sur l'élément minimum du sous tableau traité (le sous tableau correspond à la partie du tableau non triée)
# t5 : pointeur sur l'élément courant à comparer
# t6 : contient le minimum de la passe en cours, vmin
# t7 : registre temporaire afin de comparer vmin aux valeurs de la pile
#

Loop_Tri_1:
bge $t1,$t0,Fin_loop_tri_1 # tant que i<tailleTableau)

addi $t2,$t1,1 # j=i+1
move $t4,$t3 # Pointeur sur le minimum actuel : le 1er élément du sous tableau
lw $t6,0($t3) # vmin = 1er élément du sous tableau traité
addi $t5,$t3,-4 # l'élément courant à comparer est celui juste au dessus du 1er élément du sous tableau


Loop_Tri_2:
bge $t2,$t0,Fin_loop_tri_2 # tant que j<tailleTableau

lw $t7,0($t5) # tmp = *t5

bge $t7,$t6,PasDeChangementMinimum # si tmp>vmin, alors pas de changement
#Sinon vmin=tmp, et $t4 contient l'adresse du nouveau minimum trouvé
move $t6,$t7
move $t4,$t5

PasDeChangementMinimum:

addi $t5,-4 # t5 contient l'adresse de l'élément j+1
addi $t2,1 # j++

j Loop_Tri_2
Fin_loop_tri_2:

#A ce state, vmin(le registre t4) contient la valeur du minimum, t4 son adresse, et t3 l'adresse où mettre ce minimum
#Il n'y a plus qu'a effectué le changement de valeur
lw $t7,0($t3) # tmp = tableau[i]
sw $t6,0($t3) # tableau[i]=vmin
sw $t7,0($t4) # tableau[min]=tmp


addi $t3,-4 # t3 contient l'adresse du i+1 élément
addi $t1,1 # i++

j Loop_Tri_1
Fin_loop_tri_1:

#A la sortie des deux boucles, le tableau dans la pile est trié

j $ra





__start:

#On demande la saisi du tableau
jal saisiTableau

#On affiche la phrase qui dit qu'on affiche le tableau saisi, puis on affiche le tableau saisi
li $v0,4
la $a0,tabsaisi
syscall
jal printTab

#On trie le tableau qui est dans la pile
jal triTableau

#On affiche le tableau trié
li $v0,4
la $a0,tabtri
syscall
jal printTab



#Sortie propre
__exit:

lw $t0,0($sp) #t0=tailleTableau

li $t3,4
addi $t1,$t0,1 # tailleTab+1
mult $t1,$t4 # 4*(tailleTab+1)
mflo $t2 # t2=4*(tailleTab+1)
add $t2,$sp,$t2 # t2 vaut l'adresse de la case en dessous de la 1er valeur du tableau(, t1=($sp + 4*(tailleTab+1))
move $sp,$t2 #On désalloue de la pile tout le tableau et sa taille

#Sortie du programme
li $v0,10
syscall
