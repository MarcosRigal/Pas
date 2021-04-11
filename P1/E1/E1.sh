#!/bin/bash 
directorio=$1
if [ -d $directorio ]
then
for x in $(find $directorio) 
do
	nombre_sin_ruta=$(basename $x)
	echo -n "$nombre_sin_ruta <- "	
	caracteres=$(echo -n $nombre_sin_ruta | wc -m )	
	if [ $caracteres -eq 1 ]
	then
		echo "$caracteres caracter"
	else
		echo "$caracteres caracteres"
	fi		
done
fi 

if [ -d $directorio ]
then
for x in $(find $directorio) 
do
	nombre_sin_ruta=$(basename $x)
	carpeta=$(dirname $x)
	ruta_absoluta=$(pwd $carpeta)				
	caracteres=$(echo -n $nombre_sin_ruta | wc -m )	
	let modulo=$caracteres%2
	if [ $modulo != 0 ]
	then	
	i_nodo=$(stat -c "i-nodo %i" $x)
	tamanio_bytes=$(stat -c "%s" $x)
	tamanio_kilobytes=$[$tamanio_bytes/1024]
	permiso=$(stat -c "permisos: %a" $x)
	usuario=$(stat -c "%U" $x)
	grupo_usuario=$(stat -c "%G" $x)
	echo "$nombre_sin_ruta, $ruta_absoluta, $i_nodo, $tamanio_bytes bytes ($tamanio_kilobytes K), $permiso, $usuario : $grupo_usuario "
	fi	
done
fi 

