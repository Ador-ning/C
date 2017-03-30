#!/bin/bash
###shift

count=1
while [[ -n "$1" ]]; do
  echo
  echo "paramter $count = $1"
  count=$(($count + 1))
  shift
done
