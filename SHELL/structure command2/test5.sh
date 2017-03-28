#!/bin/bash
##processing txt data file

IFS=$'\n'
spec=$'\*' ########not remove the * fluence
for entry in $(cat /etc/passwd); do
  echo "In $entry ######"
  IFS=:
  for var in $entry; do
    if [[ $var = $spec ]]; then
      echo "cll"
    else
      echo "$var"
    fi
  done
done >output.txt
