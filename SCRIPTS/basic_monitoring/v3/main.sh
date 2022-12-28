#!/bin/bash

START="$(date +%s.%N)"
VOID="$(echo)"

. ./input_test.sh
. ./get_info.sh
. ./printall.sh

if ! [ "$2" == "$VOID" ]
then
	echo -e "\e[33m TOO MUCH PARAMETERS, DUMMY, THIS SCRIPT TAKES ONLY ONE PARAMETER (USAGE: ./main.sh /PLACE/YOUR/DIRECTORY) \e[0m"
	exit 1
fi

input_test $1
get_info $IFEXISTS
top5list $IFEXISTS
top10files $IFEXISTS
top10exec $IFEXISTS
EL_PRINTELLO

END="$(date +%s.%N)"
RUNTIME="$(echo "$END - $START" | bc)"
echo -e "\e[32m Script execution time (in seconds) = "$(printf "%.1f" $RUNTIME)" \e[0m"

