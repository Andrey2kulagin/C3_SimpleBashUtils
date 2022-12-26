#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE1="text.txt"
TEST_FILE2="text2.txt"

echo "Первый тест"

for var in -e -i -v -c -l -n
do
          TEST1="$var H $TEST_FILE1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
               echo "$TEST1"
          fi
          rm s21_grep*.txt grep*.txt
done


echo "Второй тест"

for var in -e -i -v -c -l -n
do
          TEST1="$var hello $TEST_FILE1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
               echo "$TEST1"
          fi
          rm s21_grep*.txt grep*.txt
done


echo "Третий тест"

for var in -e -i -v -c -l -n
do
          TEST1="$var hello $TEST_FILE1 $TEST_FILE2"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
               echo "$TEST1"
          fi
          rm s21_grep*.txt grep*.txt
done


echo "Четвертый тест"

for var in -e -i -v -c -l -n
do
          TEST1="$var h $TEST_FILE1 $TEST_FILE1 $TEST_FILE2"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
               echo "$TEST1"
          fi
          rm s21_grep*.txt grep*.txt
done


DIFF_RES=""
TEST_FILE1="text.txt"
TEST_FILE2="text2.txt"
TEST_FILE2="text2.txt"
WORD="SUn"


echo "Пятый тест"

for var in -e -i -v -c -l -n
do
TEST1="$var $WORD $TEST_FILE1"
./s21_grep $TEST1 > s21_grep.txt
grep $TEST1 > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
then
(( COUNTER_SUCCESS++ ))
else
echo "$TEST1" >> log.txt
(( COUNTER_FAIL++ ))
 echo "$TEST1"
fi
rm s21_grep*.txt grep*.txt
done

for var in -e -i -v -c -l -n #-v -E -T —number-nonblank —number —squeeze-blank
do
for test_file1 in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3
do
for test_file2 in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3
do
TEST1="$var $WORD $test_file1 $test_file2"
./s21_grep $TEST1 > s21_grep.txt
grep $TEST1 > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
then
(( COUNTER_SUCCESS++ ))
else
echo "$TEST1">> log.txt
(( COUNTER_FAIL++ ))
 echo "$TEST1"hlkhlkl
fi
rm s21_grep*.txt grep*.txt
done
done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

