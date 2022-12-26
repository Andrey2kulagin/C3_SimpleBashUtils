#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="file.txt"

echo /dev/null > log.txt
echo "Первый тест"


TEST1="$TEST_FILE"
echo "$TEST1"
./s21_cat $TEST1 > s21_cat.txt
cat $TEST1 > cat.txt
DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
  else
    echo "$TEST1" >> log.txt
    (( COUNTER_FAIL++ ))
fi
#rm s21_cat*.txt cat*.txt


for var in -b -e -n -s -t #-E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat*.txt cat*.txt
done



echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
