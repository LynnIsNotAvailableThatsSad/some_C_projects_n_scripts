#!/bin/bash

TEMP=""
HUM=""
ADDRESS=""

while true
do
	echo -e "\e[33m ENTER ADDRESS \e[0m"
	read -p ": " ADDRESS

	HUM="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t03 -r1 -a$ADDRESS | tail -1 | awk '{print $2}' |  cut -c 3-6)"
	HUM="$(printf %d $((16#$HUM)))"
	TEMP="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t03 -r0 -a$ADDRESS | tail -1 | awk '{print $2}' | cut -c 3-6)"
	TEMP="$(printf %d $((16#$TEMP)))"

	echo -e "\e[32m HUMIDITY $HUM\n TEMPERATURE $TEMP \e[0m"
	echo -e "\e[33m ENTER TEMP AND HUM TO RECORD \e[0m"
	read -p ": " TEMP HUM

	modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t06 -r300 -a$ADDRESS 0
	sleep 1
	modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t06 -r280 -a$ADDRESS $TEMP
	sleep 1
	modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t06 -r301 -a$ADDRESS 0
	sleep 1
	modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t06 -r281 -a$ADDRESS $HUM	
done
