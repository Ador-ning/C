#!/bin/bash
####

while [[ -n "$1" ]]; do
  case "$1" in
    -a)
      echo "Found -a option"
      ;;
    -b)
      para="$2"
      echo "Found the -b option, with paramter $para"
      shift
      ;;
    -c)
      echo "Found -c option"
      ;;
    --)
      shift
      break
      ;;
    *)
      echo "$1 is not an option"
      ;;
  esac
  shift
done
####
##Function ??
count=1
for para in "$@"; do
  echo "paramter #$count: $para"
  count=$(($count + 1))
done
