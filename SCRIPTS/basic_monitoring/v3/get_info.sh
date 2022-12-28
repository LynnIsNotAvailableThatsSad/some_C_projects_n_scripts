#!/bin/bash

TOP5LIST=()
TOP10FILES=()
TOP10EXEC=()

function get_info {
	DIRCOUNT="$(find "$IFEXISTS" -type d | wc -l)"
	TOTALFILECOUNT="$(find "$IFEXISTS" -type f | wc -l)"
	CONF_FILES="$(find "$IFEXISTS" -name *.conf | wc -l)"
	TEXT_FILES="$(cd "$IFEXISTS" && file * | grep ":.* text" | wc -l)"
	EXEC_FILES="$(find "$IFEXISTS" -type f  -executable | wc -l)"
	LOG_FILES="$(find "$IFEXISTS" -name *.log | wc -l)"
	ARCHIVES="$(find "$IFEXISTS" -name *.gz | wc -l)"
	SYMLINKS="$(find "$IFEXISTS" -type l | wc -l)"
}

function top5list {
	find "$IFEXISTS" -type d -printf '%s %p\n'| sort -nr | head -5 | numfmt --field=1 --to=iec >> top5dirlist.txt
	for (( i=0; i<5; i++ ))
	do
		TOP5LIST[$i]="$(cat -n top5dirlist.txt | grep "     "$(( $i + 1 ))"")"
	done
	#echo ${TOP5LIST[@]} #TEST
	rm top5dirlist.txt
}

function top10files {
	find "$IFEXISTS" -type f -printf '%s %p\n'| sort -nr | head -10 | numfmt --field=1 --to=iec >> top10files.txt
	for (( s=0; s<9; s++ ))
        do
                TOP10FILES[$s]="$(cat -n top10files.txt | grep "     "$(( $s + 1 ))"")"
		TEMPO="$(echo "${TOP10FILES[$s]}" | awk '{print $3}')"
		if [ -d "$TEMPO" ]
		then
			TOP10FILES[$s]="${TOP10FILES[$s]} $(cd "$TEMPO" && file * | awk '{printf $2"\n"}')"
		fi
	done

	TOP10FILES[10]="$(cat -n top10files.txt | grep "    10")"
        TEMPO="$(echo "${TOP10FILES[10]}" | awk '{print $3}')"
	if [ -d "$TEMPO" ]
        then
        	TOP10FILES[10]="${TOP10FILES[10]} $(cd "$TEMPO" && file * | awk '{printf $2"\n"}')"
	fi
        rm top10files.txt
}

function top10exec {
	find "$IFEXISTS" -type f -executable -printf '%s %p\n'| sort -nr | head -10 | numfmt --field=1 --to=iec >> top10exec.txt
	for (( z=0; z<9; z++ ))
	do
		TOP10EXEC[$z]="$(cat -n top10exec.txt | grep "     "$(( $z + 1 ))"")"
		TEMPO="$(echo "${TOP10EXEC[$z]}" | awk '{print $3}')"
		if ! [ "$TEMPO" == "" ]
		then
			SUM="$(sha1sum "$TEMPO" | awk '{print $1}')"
			TOP10EXEC[$z]="${TOP10EXEC[$z]} $SUM"
		fi
	done
	TOP10EXEC[10]="$(cat -n top10exec.txt | grep "    10")"
        TEMPO="$(echo "${TOP10EXEC[10]}" | awk '{print $3}')"
	if ! [ "$TEMPO" == "" ]
        then
        	SUM="$(sha1sum "$TEMPO" | awk '{print $1}')"
        	TOP10EXEC[10]="${TOP10EXEC[10]} $SUM"
	fi
	rm top10exec.txt
}

