#!/bin/bash

function EL_PRINTELLO {
echo -e "\e[32m Total number of folders (including all nested ones) = $DIRCOUNT \e[0m"
echo -e  "\e[31m TOP 5 folders of maximum size arranged in descending order (path and size): \e[0m"
	for (( i=0; i<5; i++ ))
	do
		echo -e "\e[33m $(echo "${TOP5LIST[$i]}" | awk '{print $1" - "$3", "$2"\n"}') \e[0m"
	done
echo -e "\e[32m Total number of files = $TOTALFILECOUNT \e[0m"
echo -e "\e[31m Number of: \e[0m"
echo -e "\e[33m Configuration files (with the .conf extension) = $CONF_FILES \e[0m"
echo -e "\e[33m Text files = $TEXT_FILES \e[0m"
echo -e "\e[33m Executable files = $EXEC_FILES \e[0m"
echo -e "\e[33m Log files (with the extension .log) = $LOG_FILES \e[0m"
echo -e "\e[33m Archive files = $ARCHIVES \e[0m"
echo -e "\e[33m Symbolic links = $SYMLINKS \e[0m"
echo -e "\e[31m TOP 10 files of maximum size arranged in descending order (path, size and type): \e[0m"
	for (( s=0; s<9; s++ ))
	do
		echo -e "\e[33m "$(echo "${TOP10FILES[$s]}" | awk '{print $1" - "$3", "$2","; $1=""; $2=""; $3=""; print $0}')" \e[0m"
	done
	echo -e "\e[33m "$(echo "${TOP10FILES[10]}" | awk '{print $1" - "$3", "$2","; $1=""; $2=""; $3=""; print $0}')" \e[0m"
echo -e "\e[31m TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file): \e[0m"
	for (( z=0; z<9; z++ ))
        do
                echo -e "\e[33m "$(echo "${TOP10EXEC[$z]}" | awk '{print $1" - "$3", "$2","; $1=""; $2=""; $3=""; print $0}')" \e[0m"
        done
        echo -e "\e[33m "$(echo "${TOP10EXEC[10]}" | awk '{print $1" - "$3", "$2","; $1=""; $2=""; $3=""; print $0}')" \e[0m"
}

