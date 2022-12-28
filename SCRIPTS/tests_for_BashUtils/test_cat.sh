#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
#TEST_FILE="bytes.txt"

for var in "" -b -e -n -s -t -v
do
    for TEST_FILE in weirdo.txt bytes.txt 1.txt Makefile s21_cat.c
    do
        for TEST_FILE1 in s21_cat.c FILE0 1.txt bytes.txt weirdo.txt
        do
            for TEST_FILE2 in Makefile weirdo.txt 1.txt bytes.txt s21_cat.c
            do

        TEST1="$var $TEST_FILE $TEST_FILE1 $TEST_FILE2"
        echo "$TEST1"
        ./s21_cat $TEST1 > s21_cat.txt
        cat $TEST1 > cat.txt
        DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
        if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
                (( COUNTER_SUCCESS++ ))
            else
                echo "FAILED: $TEST1"
                echo "FAILED: $DIFF_RES"
                echo "$TEST1" > log.txt
                (( COUNTER_FAIL++ ))
        fi
        rm s21_cat.txt cat.txt
            done
        done
    done
done
    echo "SUCCESS: $COUNTER_SUCCESS"
    echo "FAIL: $COUNTER_FAIL"

