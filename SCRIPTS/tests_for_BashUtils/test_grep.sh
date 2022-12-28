#!bin/bash
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt

for var in -i -v -c -l -n -h -s
do
    for TEST_FILE in 1.txt 2.txt bents.txt test.txt
    do
        for PATTERN in biba boba a GAY -
        do
            TEST1="$var $PATTERN $TEST_FILE"
            echo "$TEST1"
            ./s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( COUNTER_SUCCESS++ ))
                else
                    echo "$TEST1" >> log.txt
                    echo "$DIFF_RES" >> log.txt
                    (( COUNTER_FAIL++ ))
            fi
            rm s21_grep.txt grep.txt
        done
    done
done


for TEST_FILE2 in 1.txt 2.txt bents.txt test.txt
do
    for TEST_FILE3 in test.txt bents.txt 2.txt 1.txt
    do
        TEST2="-e biba -e boba -e GAY -e -s $TEST_FILE2 $TEST_FILE3"
        echo "$TEST2"
        ./s21_grep $TEST2 > s21_grep.txt
        grep $TEST2 > grep.txt
        DIFF_RES1="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES1" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                (( COUNTER_SUCCESS++ ))
            else
                echo "$TEST2" >> log.txt
                echo "$DIFF_RES1" >> log.txt
                (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt
    done
done


for PATTERN1 in -bi g - '\0' a b i bi
do
    TEST3="$PATTERN1 1.txt 2.txt bents.txt test.txt"
    echo "$TEST3"
    ./s21_grep $TEST3 > s21_grep.txt
    grep $TEST3 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
            (( COUNTER_SUCCESS++ ))
        else
            echo "$TEST3" >> log.txt
            echo "$DIFF_RES" >> log.txt
            (( COUNTER_FAIL++ ))
    fi
    rm s21_grep.txt grep.txt
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
