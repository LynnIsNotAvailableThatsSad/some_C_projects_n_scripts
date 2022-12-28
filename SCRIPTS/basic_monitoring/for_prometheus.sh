#!/bin/bash

while true
do
	sleep 5
	rm -f /etc/nginx/metrics
	CPU_usage="$(uptime | awk '{print $8}' | cut -b 1-4)"
	mem_total="$(free | grep Mem | awk '{print $2}')"
	mem_used="$(free | grep Mem | awk '{print $3}')"
	mem_available="$(free | grep Mem | awk '{print $7}')"
	disk_used="$(df --total | grep total | awk '{print $3}')"
	disk_available="$(df --total | grep total | awk '{print $4}')"

	metrics_name=("CPU_usage" "mem_total" "mem_used" "mem_available" "disk_used" "disk_available")
	metrics_arr=($CPU_usage $mem_total $mem_used $mem_available $disk_used $disk_available)
	counter=0
	for var in ${metrics_arr[@]}
	do
		echo "${metrics_name[$counter]} $var" >> metrics
		(( counter++ ))
	done
	mv metrics /etc/nginx/
done

