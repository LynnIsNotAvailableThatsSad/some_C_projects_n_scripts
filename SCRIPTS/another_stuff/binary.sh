#!/bin/bash

NUM1=""
NUM2=""

echo -e "\e[33m ENTER 2 NUMBERS \e[0m"
read -p ": " NUM1 NUM2

NUM1="$(echo "ibase=10;obase=2;$NUM1" | bc)"
NUM2="$(echo "ibase=10;obase=2;$NUM2" | bc)"
while [ "$(echo $NUM1 | wc -c)" -le 8 ]
do
	NUM1="$(echo 0$NUM1)"
done
while [ "$(echo $NUM2 | wc -c)" -le 8 ]
do
	NUM2="$(echo 0$NUM2)"
done

NUM_TOTAL="$(echo $NUM1$NUM2)"

NUM_TOTAL="$(echo "$((2#$NUM_TOTAL))")"
NUM_TOTAL="$(echo "ibase=10;obase=16;$NUM_TOTAL" | bc)"
echo -e "\e[32m YOUR HEX NUMBER IS: \e[0m"
echo 0x$NUM_TOTAL
