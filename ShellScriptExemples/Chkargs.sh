#! /bin/bash

if [ $# -eq 0 ]; then
	echo "Usar $0 [Agumento]" 1>&2
	exit 1
fi

echo "Executando com '$1'"
