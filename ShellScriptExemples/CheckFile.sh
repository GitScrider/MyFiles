#! /bin/bash

FILE=$*
PERMISSAO=(- - -)

if [ -e "$FILE" ]; then #existe ?
	if [ -f "$FILE" ]; then #茅 um arquivo regular
		if [ -r "$FILE" ]; then
			PERMISSAO[0]=r
		fi
		if [ -w "$FILE" ]; then
                        PERMISSAO[1]=w
                fi
		if [ -x "$FILE" ]; then
                        PERMISSAO[2]=x
         	fi

		echo "$FILE: arquivo ($( echo ${PERMISSAO[@]} | sed -e 's/[^a-z]//ig'))"

	elif [ -d "$FILE" ]; then #茅 um diret贸rio
		if [ -r "$FILE" ]; then
			PERMISSAO[0]=r
		fi
		if [ -w "$FILE" ]; then
                        PERMISSAO[1]=w
                fi
		if [ -x "$FILE" ]; then
                        PERMISSAO[2]=x
         	fi

		echo "$FILE: diret贸rio ($( echo ${PERMISSAO[@]} | sed -e 's/[^a-z]//ig'))"


	 else
		if [ -r "$FILE" ]; then
			PERMISSAO[0]=r
		fi
		if [ -w "$FILE" ]; then
                        PERMISSAO[1]=w
                fi
		if [ -x "$FILE" ]; then
                        PERMISSAO[2]=x
         	fi

		echo "$FILE: desconhecido ($( echo ${PERMISSAO[@]} | sed -e 's/[^a-z]//ig'))"
	fi



elif [ "$FILE" == "" ]; then

	echo "Usar: ./checkfile [Arquivo]" 1>&2


else
	echo "$FILE: inv谩lido"

fi
