#!/bin/sh

cd ./participants
NOMS=$(ls *.txt | sed "s/.txt//g")

for n in $NOMS
do 
	echo $n "écrit :"
	cat $n.txt
	echo""
done
