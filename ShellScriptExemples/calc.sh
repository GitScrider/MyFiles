#! /bin/bash

a=$1
op=$2
b=$3

if [ $# -ne 3 ]; then
	echo "Usar: ./calc [Número] [Operador] [Número]"
	exit 1
fi

case "$op" in
	"+")
		echo "$a + $b" | bc -l
		;;

	"-")
		echo "$a - $b" | bc -l
		;;

	"/")
		echo "$a / $b" | bc -l
		;;

	"x")
		echo "$a * $b" | bc -l
		;;
	*)
		echo "$op: operação inválida"
		;;

esac
