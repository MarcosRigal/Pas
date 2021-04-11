#!/bin/bash
if [ -d ${1} ] && [ -d ${2} ] &&[ ${3} -gt 0 ]
then
	echo "correcto"
else
	echo "error"
	exit
fi
x=0
for a in $(ls $2)
do
	let "x = $x +1 "
done
echo "hay $x ficheros en $2"
if [ $x -lt $3 ]
then
	echo "cabe otra copia"
	let "x = $x +1 "
	mkdir "$2/$x"
	for b in $(ls $1)
	do
	cp $1/$b $2/$x
	done
else
	echo "no caben mas copias"
	rm -R "$2/1"
	x=0
	for a in $(ls $2)
	do
		let "x = $x +1 "
		echo $a
		echo $x
		mv $2/$a $2/$x
	done
	let "x = $x +1 "
	mkdir "$2/$x"
	for b in $(ls $1)
	do
	cp $1/$b $2/$x
	done
fi