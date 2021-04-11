#!/bin/bash

if [ $# -ne 1 ]
then
	echo "El script debe recibir un argumento obligatoriamente."
	exit 1
fi

i=0

while read direccion
do
	#echo $direccion
	ip=$(resolveip $direccion | cut -d' ' -f6 )
	
	Array[i]=$(echo -e "$ip\t$direccion")
	let "i = $i +1"
	
done < $1

IFS=$'\n' sorted=($(sort -t . -k 1,1n -k 2,2n -k 3,3n -k 4,4n <<<"${Array[*]}")) # ordenamos el array por caracter de separacion . y columnas en orden numero.
unset IFS

for (( b=0 ; $b < ${#sorted[@]} ; b=$b+1)) # ${#sorted[@]} indica la longitud del array
do
	echo ${sorted[$b]}
done