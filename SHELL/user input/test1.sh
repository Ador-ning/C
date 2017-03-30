#!/bin/bash
###
### test paramters

if [[ $# -ne 3 ]]; then
  echo
  echo "paramters numbers error!"
  echo "pattern: command a b c"
else
  para=$#
  echo
  echo "The last paramter ${!#}"
  second=$(($# - 1)) #### 2
  echo "The second last paramter $second"
fi
