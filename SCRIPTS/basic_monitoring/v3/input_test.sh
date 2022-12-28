#!/bin/bash

IFEXISTS="$1"

function input_test {

if [ ! -d $IFEXISTS ] 
then
	echo -e "\e[33m INCORRECT DIRECTORY: DOESN'T EXIST OR WRONG FORMAT. USAGE: ./main.sh /PLACE/YOUR/DIRECTORY/ \e[0m"
	exit 1
fi
}

