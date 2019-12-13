#!/bin/bash

semana[0]="Mon"
semana[1]="Tue"
semana[2]="Wed"
semana[3]="Thu"
semana[4]="Fri"
semana[5]="Sat"
semana[6]="Sun"
x="Sat"
y="Sun"

#semana("Mon""Tue""Wed""Thu""Fri""Sat""Sun")

#str=${semana[$i]}
#echo "$str"

for ((i=0;i<7;i++)); do
	str=${semana[$i]}
	if [ "$y"=="$str" ] || [ "$x" == "$str" ]; then
		echo "${semana[$i]} (weekend)"
	else
		echo "${semana[$i]} (weekday)"
	fi
done

#!/bin/bash


n=$(echo | cat /etc/passwd | wc -l )
n=$((n+1))

for ((i=1; i < $n ;i++)); do
	str=$(echo | cat /etc/passwd | awk -F: 'NR=='$i' {print $1}')
	echo "User $i: $str"

done

#!/bin/bash

for ((i=0;i<6;i++)); do
	echo "Dice $((i+1)): $((1+RANDOM%6))"
done

#!/bin/bash

n=0
for arg; do
	input[n]=$arg
	n=$((n+1))

done

l=${input[0]}
h=${input[0]}

echo $h $l


for ((i=0; i<$n;i++)); do
	if [ $l -gt ${input[$i]} ]; then
		l=${input[$i]}
	fi
	if [ $h -lt ${input[$i]} ]; then
		h=${input[$i]}
	fi

done


echo "Lower: $l"
echo "Higher: $h"

#!/bin/bash

trap '' 1 2 3 6 9 18 19

n1=$(($RANDOM%999+1))
n2=$(($RANDOM%999+1))

sinal=$(($RANDOM%1))

case $sinal in
	0)
	op='-'
	;;
	1)
	op='+'
	;;
esac
printf "  %5d\n  %c %3d\n  -----\n?" $n1 $op $n2


resposta=-10000
r=$(expr $n1 $op $n2)


while [ $r -ne $resposta ]; do
	read resposta
	if [ $resposta -ne $r ]; then
		printf "Wrong answer \n? "


	fi
done

echo "Right answer"

#!/bin/bash



echo "Try to guess the numer I thought!"
n=$(($RANDOM%1000+1))
echo "Choose a number (1 to 1000)"
read c
while [ $n -ne $c ]; do

	until [ $c -eq $n ]; do
		echo "Choose a number (1 to 1000)"
		if [ $c -lt $n ]; then
			echo " My number is higher than $c"
		else
			echo " My number is lower than $c"
		fi
		read c
	done

done


echo "Congratulaitons"

#!/bin/bash

while read line
do

	newline=$(echo $line | tr 'A-Z' 'a-z' | sed "s/[^a-z]//g")
	#echo $newline
	revline=$(echo $newline | rev)
	#echo $revline
	if [ "$newline" == "$revline" ]; then
		echo "Yes"
	else
		echo "No"
	fi
done
