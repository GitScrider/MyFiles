#! /bin/bash

input=(um dois tres)
aux=0

echo -n "Primeiro número: "
read input[0]
echo -n "Segundo número: "
read input[1]
echo -n "Terceiro número: "
read input[2]

sorted=($(echo ${input[*]} | tr " " "\n" | sort -n))

echo "O maior número é ${sorted[2]}"
