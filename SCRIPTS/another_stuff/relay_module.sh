#!/bin/bash

MARK=""
RELAY_NUM=""
RELAY_STAT=""
ADDR=""
OPTION=""



echo -e "\e[32m ###################################### \e[0m"                                               
read -p "ВВЕДИ MODBUS-АДРЕС: " ADDR                                                                       
echo -e "\e[32m ###################################### \e[0m"

while :
do
modbus_client --debug -mrtu -pnone -s2 /dev/ttyRS485-1 -a$ADDR -t0x06 -r40 9 | tail -1
modbus_client --debug -mrtu -pnone -s2 /dev/ttyRS485-1 -a$ADDR -t0x06 -r41 144 | tail -1

	echo -e "\e[32m ###################################### \e[0m"
	echo -e "\e[33m ЧТОБЫ ВЫЙТИ, ВВЕДИ Q+ENTER \e[0m"
	echo -e "\e[33m ЗАМКНУТЬ К1 - ВВЕДИ 11 \e[0m"
	echo -e "\e[33m ЗАМКНУТЬ К2 - ВВЕДИ 21 \e[0m"
	echo -e "\e[33m РАЗОМКНУТЬ К1 - ВВЕДИ 10 \e[0m"
	echo -e "\e[33m РАЗОМКНУТЬ К2 - ВВЕДИ 20 \e[0m"
	echo -e "\e[33m ЗАМКНУТЬ К1 и К2 СРАЗУ - ВВЕДИ 31 \e[0m"
	echo -e "\e[33m РАЗОМКНУТЬ К1 и К2 СРАЗУ - ВВЕДИ 30 \e[0m"
	read -p ": " MARK
	echo -e "\e[32m ###################################### \e[0m"
		case $MARK in
			21)
				RELAY_NUM=1
				RELAY_STAT=1
				;;
			20)
				RELAY_NUM=1
				RELAY_STAT=0
				;;
			11)
				RELAY_NUM=0
				RELAY_STAT=1
				;;
			10)
				RELAY_NUM=0
				RELAY_STAT=0
				;;
			31)
				RELAY_STAT=1
				;;
			30)
				RELAY_STAT=0
				;;
			Q)
				exit 1
				;;
			*)
				echo -e "\e[31m НЕТ ТАКОЙ ОПЦИИ! \e[0m"
				ERR_FLAG=1
				;;
		esac	
	if ! [ "$ERR_FLAG" == 1 ]
	then	
		if [ "$MARK" == "31" ] || [ "$MARK" == "30" ]
		then
			echo -e "\e[32m ###################################### \e[0m"
			echo -e "\e[35m РЕЛЕ 1: ЗАПИСЬ СТАТУСА "$RELAY_STAT: "\e[0m"
			modbus_client --debug -mrtu -pnone -s2 /dev/ttyRS485-1 -a"$ADDR" -t5 -r0 "$RELAY_STAT" | grep -e SUCCESS -e ERROR
			echo -e "\e[32m ###################################### \e[0m"
			echo -e "\e[35m РЕЛЕ 2: ЗАПИСЬ СТАТУСА "$RELAY_STAT": \e[0m"
			modbus_client --debug -mrtu -pnone -s2 /dev/ttyRS485-1 -a"$ADDR" -t5 -r1 "$RELAY_STAT" | grep -e SUCCESS -e ERROR
			echo -e "\e[32m ###################################### \e[0m"
		else
			echo -e "\e[32m ###################################### \e[0m"
			echo -e "\e[35m РЕЛЕ "$RELAY_NUM" ЗАПИСЬ СТАТУСА "$RELAY_STAT": \e[0m"
			modbus_client --debug -mrtu -pnone -s2 /dev/ttyRS485-1 -a"$ADDR" -t5 -r"$RELAY_NUM" "$RELAY_STAT" | grep -e SUCCESS -e ERROR
			echo -e "\e[32m ###################################### \e[0m"
		fi
	fi

ERR_FLAG=""	
done
