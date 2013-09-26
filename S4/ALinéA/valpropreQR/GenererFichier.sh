#!/bin/sh

if [ $# -lt 2 ]
then
	echo "Usage : ./GenererFichier.sh <nom du fichier de donnée> <nom du fichier a charger dans gnuplot>"
	exit 1
fi

iteration=`tail -n 1 $1`
taille=`tail -n 2 $1 | head -n 1`
i=0

echo "set xr [-1:$taille]" > $2
echo "set yr [-1:$taille]" >> $2

while [ $i -lt $iteration ]
do
	echo "plot '$1' index $i" >> $2
	echo "pause -1" >> $2
	i=`expr $i + 1`
	
done
