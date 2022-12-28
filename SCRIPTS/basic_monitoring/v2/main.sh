#!/bin/bash

CB1=""
CF1=""
CB2=""
CF2=""
CPOOL=("$CB1" "$CF1" "$CB2" "$CF2")

. ./get_info.sh
. ./input_test.sh
. ./get_colors.sh
. ./printfile.sh

if ! [ "$5" == "$VOID" ]
then
	echo -e "\e[33m THAT'S MORE, THAN FOUR, GOD DAMN IT!!!11 \e[0m"
	exit 1
fi

input_test $1 $2 $3 $4
get_colors $1 $2 $3 $4
getdata
printfile

