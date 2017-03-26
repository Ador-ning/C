#!/bin/bash
##(( expression )) and [[ expression ]]

##
val=10
val2=2

if (($val ** 2)); then
  ((val3 = $val ** 2))
  echo "$val3"
  ((val4 = val2 << val))
  echo "$val4"
fi

##
if [[ $USER == n* ]]; then
  echo "hello $USER"
else
  echo "Don't know"
fi
