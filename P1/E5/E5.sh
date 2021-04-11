#!/bin/bash
hash="$(cat "hash.txt")"
comb=16
echo "Probando las $comb combinaciones de longitud 1"
for i in $(eval echo {{0..9},{A..F}})
do
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Encontrado! es $i"
        exit
    fi
done
let "comb = $comb * 16"
echo "Probando las $comb combinaciones de longitud 2"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}})
do
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Encontrado! es $i"
        exit
    fi
done
let "comb = $comb * 16"
echo "Probando las $comb combinaciones de longitud 3"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}})
do
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Encontrado! es $i"
        exit
    fi
done
let "comb = $comb * 16"
echo "Probando las $comb combinaciones de longitud 4"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}})
do
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Encontrado! es $i"
        exit
    fi
done
let "comb = $comb * 16"
echo "Probando las $comb combinaciones de longitud 5"
for i in $(eval echo {{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}}{{0..9},{A..F}})
do
    try="$(echo $i | sha256sum)"
    if [ "$try" == "$hash" ]
    then 
        echo "Encontrado! es $i"
        exit
    fi
done