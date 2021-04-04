#!/bin/bash

read -p "Introduzca un primer numero:" n1
read -p "Introduzca un segundo numero:" n2

echo "Suma: $[$n1+$n2]"
echo "Resta: $[$n1-$n2]"
echo "Multiplicación: $[$n1*$n2]"
echo "Division: $[$n1/$n2]"
echo "Módulo: $[$n1%$n2]"