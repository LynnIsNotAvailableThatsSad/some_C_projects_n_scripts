#!/bin/bash

function by_code {
case $1 in
	"")
		i=0
		;;
	"err")
		i=2
		;;
esac
local ARR=("200" "201" "400" "401" "403" "404" "500" "501" "502" "503")	
while [[ $i -lt 10 ]]
do
	awk '$9=='${ARR[$i]}'{print $0}' ../04/*.log #>> test.txt
	(( i++ ))
done
}

function by_unique_ip {
case $1 in
	"")
		local string="../04/*.log"
		;;
	"EXPLOSIONS")
		local string="buff.txt"
		;;
esac
	awk '!seen[$1] {print $1}
	{++seen[$1]}' $string
}

function by_your_mom {
by_code err >> buff.txt
by_unique_ip EXPLOSIONS
rm -f buff.txt
}

