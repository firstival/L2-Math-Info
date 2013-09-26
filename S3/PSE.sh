#!/bin/sh

topn=5
ordretri=2
clock=`getconf CLK_TCK`
stop=1
killlist=

demarrage()
{
	echo "\n\t\t\t\t`cat /proc/version | cut -d" " --field=1,3`"
	up=`cat /proc/uptime | cut -d"." -f1`
	dateboot=`date -d "$up seconds ago"`
	echo "\n\n\tDernier Démarrage : $dateboot\n"
	usercount=`who | cut -d" " -f1 | sort -u | wc -l`
	if [ $usercount -gt 1 ]
	then s="s"
	fi
	echo "\tIl y a actuellement $usercount utilisateur$s connecté$s\n"
	load=`cat /proc/loadavg | cut -d" " --field=1,2,3 | sed "s/ / \/ /g"`
	echo "\tCharge moyenne du processeur(sur 1min/5min/15min) : $load\n"
	memtotal=`grep "MemTotal" /proc/meminfo | tr -s " " | cut -d" " -f2`
	memfree=`grep "MemFree" /proc/meminfo | tr -s " " | cut -d" " -f2`
	memcached=`grep "^Cached" /proc/meminfo | tr -s " " | cut -d" " -f2`
	membuffer=`grep "Buffers" /proc/meminfo | tr -s " " | cut -d" " -f2`
	memuse=`expr $memtotal - $memfree - $memcached - $membuffer`
	moy_usage_ram=`expr $memuse \* 100 / $memtotal`
	echo "\tUtilisation moyenne de la RAM : $moy_usage_ram%\n" 
}


topfichier()
{
	chemin=`pwd`
	nbfichier=`du -s $chemin/* | wc -l`
	if [ $nbfichier -lt $1 ]
	then topnfichier=$nbfichier
	else topnfichier=$1
	fi
	
	echo "Les $topnfichier fichiers ou répertoire prenant le plus de place dans \"$chemin\" :"
	echo "SIZE\tNAME"
	du -s $chemin/* | sort -nr | head -$topnfichier
	echo
}

topps()
{
	nbps=`ls -d /proc/[0-9]*/stat 2>/dev/null| wc -l`
	if [ $nbps -lt $1 ]
	then topnps=$nbps
	else topnps=$1
	fi

	cat /proc/[0-9]*/stat > /tmp/tops_awk.$$ 2>/dev/null
	awk '{print $1,$14+$15+$16+$17,$23,$18,$22 }' /tmp/tops_awk.$$ >>/tmp/tops.$$
	cat /tmp/tops.$$ | sort -k$ordretri,$ordretri -nr | head -$topnps > /tmp/topps.$$
	echo "Nombre total de processus affichés : $topnps"
	echo "PID;TEMPS CPU;VSIZE;PRIO;STARTTIME"
	while read i
	do
			pidtmp=`echo $i | cut -d" " -f1`
			cputmp=`echo $i | cut -d" " -f2`
			vsizetmp=`echo $i | cut -d" " -f3`
			priotmp=`echo $i | cut -d" " -f4`
			timetmp=`echo $i | cut -d" " -f5`
			cputmp=`expr $cputmp / $clock`"sec"
			vsizetmp=`expr $vsizetmp / 1000000`"Mo"
			timetmp=`expr $up - $timetmp / $clock`
			timetmp=`date -d "$timetmp seconds ago"`
			echo "$pidtmp;$cputmp;$vsizetmp;$priotmp;$timetmp"
	done </tmp/topps.$$

	rm /tmp/tops.$$
	rm /tmp/topps.$$
	rm /tmp/tops_awk.$$
}

fun_kill()
{
	killetat=`echo killlist | grep $1 | cut -d" " -f2`
	if [ -z $killetat ]
	then killlist=$killlist"$1 hup\n"
	kill -1 $1 && echo "$1 killed by SIGHUP"
	else if [ $killetat = hup ]
	then killlist=`sed "s/$1 hup/$1 int/g"`
	kill -2 $1 && echo "$1 killed by SIGINT"
	else killlist=`sed "s/$1 hup/$1 int/g"`
	kill -9 $1 && echo "$1 killed by SIGKILL"
	fi fi
}

demarrage
topfichier $topn
topps $topn | column -t -s";"

while [ $stop = 1 ]
do
	echo "\nQue voulez vous faire ?"
	top=$topn
	read cmd
	cmd1=`echo $cmd | cut -d" " -f1`
	cmd2=`echo $cmd | cut -d" " -f2`
	case $cmd1 in
		top)
			if [ $cmd2 = top ]
			then
			topfichier $top
			topps $top
			else
			top=$cmd2
			topfichier $top
			topps $top  | column -t -s";"
			fi
			;;
		cd)
			eval $cmd
			;;
		sort)
			if [ $cmd2 = cpu ]
			then ordretri=2
			else if [ $cmd2 = prio ]
			then ordretri=4
			else if [ $cmd2 = vsize ]
			then ordretri=3
			else if [ $cmd2 = starttime ]
			then ordretri=5
			fi fi fi fi
			;;
		kill)
			fun_kill $cmd2
			;;
		renice)
			eval $cmd
			;;
		quit)
			stop=0
			;;
		*)
		echo "Usage :\ntop <N> : affiche les N plus gros fichiers/répertoire, et les N processus trié (l'ordre de tri par défaut est par temps CPU),si N est égal à 5 par defaut
			\ncd <chemin> : changer de chemin d'accès pour <chemin>
			\nsort [cpu | prio | vsize | starttime] : change l'ordre de tri des processus
			\nkill <pid> : tue le processus dont le PID est celui renseigné
			\nrenice <pid> <val> : change la priorité du processus dont le PID est <pid>, à la valeur <val>
			\nquit : quitte le script"
	esac
done
