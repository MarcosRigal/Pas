#!/bin/bash

if [ -f ${1} ];
then
   cp ${1} ${1}.bak_$(date +%d-%m-%y)
   echo "Hecho"
else
   echo "No existe el archivo"
   exit 1
fi