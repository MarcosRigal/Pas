#Script que muestra por pantalla los ficheros de la carpeta que especifiquemos por linea de comandos
#Muestra el número de caracteres del nombre del fichero
#De los fichero con longitud impar, muestra una serie de propiedades
#Ejemplo de ejecución: ./ej1.sh nombre_carpeta

#!/bin/bash 
# $1 se refiere al primer argumento de la linea
directorio=$1
if [ -d $directorio ]
then
for x in $(find $directorio) 
do
	nombre_sin_ruta=$(basename $x) #basename devuelve el nombre del fichero sin la ruta donde se encuentra
	echo -n "$nombre_sin_ruta <- "	
	caracteres=$(echo -n $nombre_sin_ruta | wc -m )	
	if [ $caracteres -eq 1 ] #comparacion numeros impares
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
	carpeta=$(dirname $x)	 #devuelve la carpeta donde se aloja el fichero
	ruta_absoluta=$(pwd $carpeta) #pwd para devolver la ruta absoluta de la carpeta				
	caracteres=$(echo -n $nombre_sin_ruta | wc -m )	
	#calculo modulo de caracteres para saber si es impar o par		
	let modulo=$caracteres%2
	if [ $modulo != 0 ]
	then	
	#mirando el man stat se pueden sacar todos.
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

