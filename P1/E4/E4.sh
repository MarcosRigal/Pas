#!/bin/bash
opcion=1
while [ $opcion -ne 0 ]
do
	echo "Seleccione un opcion" 
	echo "1.Nombre usuario"
	echo "2.Nombre del host"
	echo "3.Ruta completa"
	echo "4.Ultima parte de la ruta"
	echo "5.Hora"
	echo "6.Fecha"
	echo "7.Cadena literal"
	echo "8.Confimar"
	echo "0.Salir"
	read opcion
	case $opcion in			
		1)	export var="\u";;	
		2)	export var="\h";;
		3)	export var="\w";;
		4)	export var="\W";;
		5)	export var="\t";;
		6)	export var="\d";;
		7)	read var;;
		8)	PROMPT_COMMAND="PS1='$PS1'; unset PROMPT_COMMAND" bash;;
	esac
	PS1="$PS1$var"
	echo "PROMT ACTUAL: $PS1"
done