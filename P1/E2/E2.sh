#!/bin/bash
if [ -d ${1} ] && [ ${2} -gt 0 ]
then
	echo "correcto"
	for a in $(ls ${1})
	do
		let "x = $x + 1"
	done
	echo "Hay $x ficheros y directorios en ${1}"
	if [ ${2} -gt $x ]
	then
		echo "Error, el numero de archivos es menor que el numero de grupos"
		exit
	fi
	if [ $[x%${2}] -ne 0 ]
	then
		echo "Error, no se puede dividir en partes iguales"
		exit
	fi
else
	echo "Fallo"
	exit
fi
let size=$[x/${2}]
echo "El tamaño de grupo es $size"
mkdir groups
for var in $( seq ${2} )
do
	mkdir "groups/group$var"
done
a=0
for b in $(ls ${1})
do
cp $1$b groups/group$[a/$size+1]
let "a = $a + 1"
done
