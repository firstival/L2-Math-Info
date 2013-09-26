#!/bin/sh

precedent_total=0
precedent_idle=0

for c  in `seq 1 4`
do
totalcpu=`cat /proc/stat | grep "^cpu " | sed 's/  / /g' | sed 's/cpu //g' | sed 's/ / + /g'`
idle=`echo $totalcpu | cut -d"+" -f4 | tr -s " "`

totalcpu=$(($totalcpu))
diff_total=$(($totalcpu - $precedent_total))
diff_idle=$(($idle-$precedent_idle))
usagecpu=$(((100*($diff_total-$diff_idle)/$diff_total)))

precedent_total=$totalcpu
precedent_idle=$idle
sleep 0.5
done

echo "\t Utilisation moyenne du processeur : ${usagecpu}%"