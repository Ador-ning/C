#!/bin/bash
## C for styles

for ((i = 0, j = 8; i < 10; i++, j--)); do
  k=$(($i + $j))
  echo $k
done

#### while loop
var=10
test3=5
while [[ $var -gt 0 ]]; do
  echo "$var $test3"
  result=$(($var - $test3))
  echo "$result"
  var=$(($var - 1))
  test3=$(($test3 + 1))
done
