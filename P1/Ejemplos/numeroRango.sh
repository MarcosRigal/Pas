#!/bin/bash

read -p "Introduzca un numero (1 <= x < 10): " numero
if [ $numero -lt 1 -o $numero -ge 10 ];
then
   echo "Fuera de rango!"
else
   echo "El numero $numero es correcto"
fi