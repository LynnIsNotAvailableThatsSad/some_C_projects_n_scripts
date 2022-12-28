#!/bin/bash

IFS=$'\n'
CB1=""
CF1=""
CB2=""
CF2=""

function printfile {
for (( i=0; i<16; i++ ))
do
	echo -e "\e["${CPOOL[0]}";"${CPOOL[1]}"m "${NAME[i]}" \e[0m = \e["${CPOOL[2]}";"${CPOOL[3]}"m "${VALUE[i]}" \e[0m"
done
}

