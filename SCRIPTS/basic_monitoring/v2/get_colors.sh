#!/bin/bash

WHITE=97 #1
RED=31 #2
GREEN=32 #3
BLUE=34 #4
PURPLE=35 #5
BLACK=30 #6
i=0

function get_colors {
for INPUTVALUES in "$1" "$2" "$3" "$4"
do
	for CHOOSE_COLOR in 1 2 3 4 5 6
	do
		if [ "$INPUTVALUES" == "$CHOOSE_COLOR" ]
		then
			case "$INPUTVALUES" in
			1) CPOOL[i]=97 ;;
			2) CPOOL[i]=31 ;;
			3) CPOOL[i]=32 ;;
			4) CPOOL[i]=34 ;;
			5) CPOOL[i]=35 ;;
			6) CPOOL[i]=30 ;;
			esac
			i=$(( $i + 1 ))
		fi

	done
done
CPOOL[0]=$(( ${CPOOL[0]} + 10 ))
CPOOL[2]=$(( ${CPOOL[2]} + 10 ))
}

