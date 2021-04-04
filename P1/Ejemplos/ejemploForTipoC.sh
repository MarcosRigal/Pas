#!/bin/bash

#for (( EXPR1 ; EXPR2 ; EXPR3 ))
#do
#instrucciones ;
#done

echo -n "Introduzca un número : "; read x ;
let sum=0
for (( i=1; $i<$x; i=$i+1 ))
do
   let "sum=$sum + $i"
done
echo "La suma de los primeros $x números naturales es: $sum "