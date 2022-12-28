#!/bin/bash

VOID=$(echo)

function input_test {
if [ "$4" == "$VOID" ]
then
	echo -e "\e[33m CAN'T YOU EVEN COUNT TO FOUR?? WHAT A SHAME!! SCRIPT REQUIRES FOUR ARGUMENTS, YOU DUMMY!!1 \e[0m"
	exit 1
fi
for ARGS in "$1" "$2" "$3" "$4"
do
        case "$ARGS" in
        1) ;;
        2) ;;
        3) ;;
        4) ;;
        5) ;;
        6) ;;
        "$VOID") ;;
        *) echo -e "\e[33m WRONG ARGUMENT - \"$ARGS\"!! SCRIPT TAKES FOUR ARGS AMONG NUMBERS FROM 1 TO 6 ONLY!!!1 \e[0m" && exit 1
        esac
done

if [ "$1" == "$2" ] || [ "$3" == "$4" ]
then
	echo -e "\e[33m OK, I'LL DO IT FOR YOU, BUT KEEP IN MIND, THAT YOU WON'T SEE THE TEXT BECAUSE YOU CHOSE THE SAME COLOR FOR THE BACKGROUND AND FONT, YOU DAMN GENIUS. HIGHLY RECOMMEND YOU TO RESTART THE SCRIPT WITH CORRECT PARAMETERS! \e[0m"
fi

}


