#!/bin/bash

# VERSION v2.1(14.11.2022)

function SetManuallyMSW {
local OPTION=""
NEWVAL=""
local OLDVAL=""

echo -e "\e[33;1m ПОДКЛЮЧИ ДАТЧИК! \e[0m"
echo -e "\e[33;1m ВВЕДИ НОВЫЙ АДРЕС, КОТОРЫЙ ХОЧЕШЬ УСТАНОВИТЬ И НАЖМИ ENTER ИЛИ M+ENTER, ЧТОБЫ ВЕРНУТЬСЯ В МЕНЮ. \e[0m"

case $1 in
	auto)
		read -p ": " NEWVAL
		BusAsk 0x80
		OLDVAL=$s
		;;
	man)
		read -p "ВВЕДИ СТАРЫЙ{пробел}НОВЫЙ АДРЕСА " OLDVAL NEWVAL
		;;
esac
if [ "$NEWVAL" == "M" ] || [ "$OLDVAL" == "M" ]
then
	exec ./multidatchik_v2.sh
else
	OPTION="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t0x06 -o100 -r0x80 -a$OLDVAL $NEWVAL  | grep SUCCESS: | awk '{print $1}')"
	if [ "$OPTION" == "SUCCESS:" ]
	then
		echo -e "\e[32;1m АДРЕС $NEWVAL УСТАНОВЛЕН, ПРОБУЮ ЕГО ОПРОСИТЬ... \e[0m"
		sleep 1
		OPTION="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t0x03 -o100 -r0x80 -a$NEWVAL 2> /dev/null | grep SUCCESS: | awk '{print $1}')"
		if [ "$OPTION" == "SUCCESS:" ]
		then
			echo -e "\e[32;1m АДРЕС $NEWVAL ОТВЕТИЛ! \e[0m"
		else
			echo -e "\e[31;1m АДРЕС $NEWVAL НЕ ОТВЕТИЛ! \e[0m"
		fi
	else
		echo -e "\e[31;1m АДРЕС $NEWVAL НЕ УСТАНОВЛЕН \e[0m"
	fi
fi
}

function BusAsk {
s=""
for (( s=1; s<255; s++ ))
do
		local chkaddr="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t0x03 -o50 -r$1 -a"$s" 2> /dev/null | grep SUCCESS: | awk '{print $1}')"
		if [ "$chkaddr" == "SUCCESS:" ]
		then
			echo -e "\e[32;1m ВЕЛИКОЛЕПНО! НАШЕЛ АДРЕС - "$s"! \e[0m"
			break
		fi
done
}

function print_menu {
	echo -e "\e[42;34;4m МЕНЮ: \e[0m"
	echo
	echo -e "\e[33;1;4m ЗАДАТЬ АДРЕС ввести 'msw' \e[0m"
	echo
	echo -e "\e[33;1;4m ЗАДАТЬ АДРЕС И СТОП-БИТ  - ввести 'wb' \e[0m"
	echo
	echo -e "\e[33;1;4m СТЕНД - ввести 'std' \e[0m"
	echo
	echo -e "\e[33;1;4m ОПРОСИТЬ ШИНУ В ПОИСКАХ АДРЕСА ПО ЗАДАННОМУ РЕГИСТРУ - ввести 'bus' \e[0m"
	echo
	echo -e "\e[33;1;4m ВЕРСИЯ СКРИПТА - ввести 'V' \e[0m"
	echo
	echo -e "\e[33;1;4m ВЫХОД - ввести 'Q' \e[0m"
	echo

}

function REMEMBER_NO_DRIVERS {
KILLA="$(ps | grep "/opt/inspark/vdrive/vdrive -c /etc/vdrive.json" | awk '{print $1}')"
kill $KILLA 2> /dev/null
}

function stand {
stand_addr=$1
local STATUS=""
while [[ $stand_addr -le 30 ]]
do
  echo -e "\e[33;1m ПОДКЛЮЧИ СЛЕДУЮЩИЙ ДАТЧИК [[ АДРЕС 1 ПО УМОЛЧАНИЮ ]]! \e[0m"
  echo -e "\e[33;1m ЖМИ ENTER, ЧТОБЫ ПРОДОЛЖИТЬ ИЛИ M+ENTER, ЧТОБЫ ВЕРНУТЬСЯ В МЕНЮ! \e[0m"
  read -p ": " STATUS
  if [ "$STATUS" == "M" ]
  then
	  exec ./multidatchik_v2.sh
  else
	STATUS="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t0x06 -o100 -r0x80 -a1 $stand_addr 2>/dev/null | grep SUCCESS: | awk '{print $1}')"	
	if [ "$STATUS" == "SUCCESS:" ]
	then
		echo -e "\e[32;1m АДРЕС $x ЗАДАН, ПРОБУЮ ОПРОСИТЬ... \e[0m"
		sleep 1
		STATUS="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t0x03 -o100 -r0x80 -a$stand_addr 2> /dev/null | grep SUCCESS: | awk '{print $1}')"
		if [ "$STATUS" == "SUCCESS:" ]
		then
			echo -e "\e[32;1m АДРЕС $stand_addr ЗАДАН И ОТВЕТИЛ НА ЗАПРОС! ТЫ ВОСХИТИТЕЛЕН! \e[0m"
			(( stand_addr++ ))
		else
			echo -e "\e[31;1m  АДРЕС $stand_addr НЕ ОТВЕТИЛ! \e[0m" 
		fi
	else
		echo -e "\e[31;1m  АДРЕС $stand_addr НЕ УСТАНОВЛЕН! \e[0m" 
	fi
  fi
done
}

REMEMBER_NO_DRIVERS
print_menu

read -p "ШО ДЕЛАЕМ? " OPTIONERO

case $OPTIONERO in
	msw)
		while :
		do
			SetManuallyMSW auto
		done
		;;
	wb)
		while :
		do
			SetManuallyMSW man
			echo -e "\e[33;1m УСТАНАВЛИВАЮ СТОП-БИТ... \e[0m"
			OPTIONERO="$(modbus_client --debug -mrtu -s2 -pnone /dev/ttyRS485-1 -t0x06 -r112 -a$NEWVAL 1 2>/dev/null | grep "SUCCESS:" | awk '{print $1}')"
			if [ "$OPTIONERO" == "SUCCESS:" ]
			then
				echo -e "\e[32;1m СТОП-БИТ УСТАНОВЛЕН! \e[0m"
			else
				echo -e "\e[31;1m СТОП-БИТ НЕ УСТАНОВЛЕН! \e[0m"
			fi
		done
		;;
	std)
		echo -e "\e[34;107;1m ВВЕДИ СТАРТОВЫЙ АДРЕС \e[0m"
		read -p ": " OPTIONERO
		for (( i=0; i<4; i++ ))
		do
			stand $OPTIONERO
		done
		;;
	bus)
		echo -e "\e[34;107;1m ВВЕДИ РЕГИСТР ДЛЯ ПОИСКА АДРЕСА ИЛИ ЖМИ ENTER, ЧТОБЫ ИСПОЛЬЗОВАТЬ ЗНАЧЕНИЕ ПО УМОЛЧАНИЮ (0x80) \e[0m"
		read -p ": " register
		if ! [ "$register" ]
		then
			register="0x80"
		fi
		BusAsk $register
		exec ./multidatchik_v2.sh
		;;
	V)
		VERSION="$(sed -n 3p multidatchik_v2.sh | awk '{print $3}')"
		echo -e "\e[34;107;1m ИСПОЛЬЗУЕМАЯ ВЕРСИЯ - $VERSION \e[0m"
		exec ./multidatchik_v2.sh
		;;
	Q)
		echo -e "\e[34;107;1m GOODBYE! \e[0m"
		exit 0
		;;
	*)
		echo -e "\e[31;1m НЕТ ТАКОЙ ОПЦИИ, ДУБИНА! \e[0m"
		exec ./multidatchik_v2.sh
		;;
esac
