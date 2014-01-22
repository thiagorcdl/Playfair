#!/bin/bash

if [ $# -lt 0 ]; then
	echo "Modo de uso: $ ./decript.sh texto.cript [texto.parcial]"
	exit 1
fi

for word in `cat seis.dict` ; do
	echo $word
	./decript $word < $1 > ./out/$1.$word.out 
	if [ $# -eq 2 ]; then
		if [[ -z `diff ./out/$1.$word.out $2` ]]; then
			echo "Chave encontrada: $word"
			break
		fi
	fi
done

exit 0
