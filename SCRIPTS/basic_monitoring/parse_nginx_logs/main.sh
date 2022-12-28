#!/bin/bash

. ./sort.sh

case $1 in
	"1")
		by_code
		;;
	"2")
		by_unique_ip
		;;
	"3")
		by_code err
		;;
	"4")
		by_your_mom
		;;
	*)
		echo -e "\e[31m INVALID OPTION. ONLY NUMBERS FROM 1 TO 4. \e[0m"
		exit 0
		;;
esac

