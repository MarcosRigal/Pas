#!/bin/bash

#until expresion_evalua_a_true
#do
#   instrucciones
#done

echo -n " Introduzca un número : "; read x
until [ "$x" -le 0 ]; do
   echo $x
   x=$(( $x -1))
   sleep 1
done
echo " TERMINADO "