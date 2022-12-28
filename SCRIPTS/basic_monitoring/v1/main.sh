#!/bin/bash

OPTION=""

. ./get_info.sh
. ./input_test.sh
. ./printfile.sh

getdata
printfile

read -p "Record this to a status-file? [Y/N]: " OPTION

if [ "$OPTION" == "Y" ] || [ "$OPTION" == "y" ]
then
    FILENAME="$(date +"%d_%m_%y_%H_%M_%S")"
	printfile >> $FILENAME.status
fi

