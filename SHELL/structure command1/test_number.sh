#!/bin/bash
#
## Testing the test command

#### In number
value1=3
value2=5

if test $value1 -gt $value2; then
  echo "value1 is greater than value2"
elif test $value2 -le 0; then
  echo "value2 is less than 0"
else
  echo "value2 is greater than 0"
fi

#### In string
string1="string"
string2="string1"
string3="strinf"

if [ -z $string1 ]; then
  echo "$string1 length is 0"
elif [ $string1 = $string2 ]; then
  echo "$string1 > $string2"
else
  echo "$string3"
fi
#### In file
file1="hi"
file2="li"

if [ -e $file1 ]; then
  echo "$file1 exsit"
  if [ $file1 -ot $file2 ]; then
    echo "$file2 newer than $file1"
  fi
else
  echo "$file1 not exsit"
fi
