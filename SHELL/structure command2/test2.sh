#!/bin/bash
##
list="Aa Bb Cc Deee Fll Frrre"
list=$list" Print"

for var in $list; do
  echo "$var"
done

##reading values from a file
file="test"
for var in $(time); do
  echo "$var"
done

IFS=$'\n'
for ca in $(ls -l); do
  echo "$ca"
done
