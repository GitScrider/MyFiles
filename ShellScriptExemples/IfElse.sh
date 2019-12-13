#! /bin/bash

x=$1

if [ $x -eq 0 ]; then
	echo "is zero"
elif [ $x -lt 0 ]; then
	echo "negative"
else
	echo "positive"
fi
