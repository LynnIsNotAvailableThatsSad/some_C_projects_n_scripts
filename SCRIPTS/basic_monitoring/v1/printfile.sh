#!/bin/bash
IFS=$'\n'

function printfile {
for (( i=0; i<16; i++ ))
do
	printf "%s\n" ${TESTARR[i]} 
done
}

