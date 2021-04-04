#!/bin/bash

#while expresion_evalua_a_true
#do
#  instrucciones
#done

echo -n "Introduzca un número: "; read x
let sum=0; let i=1
while [ $i -le $x ]; do
let "sum = $sum + $i"
let "i = $i + 1"
done
echo "La suma de los primeros $x números es: $sum "