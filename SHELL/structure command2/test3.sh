#!/bin/bash

##
for file in /Users/ning/*; do
  if [[ -d "$file" ]]; then
    echo "Directory $file"
  else
    echo "File $file"
  fi
  ####Can using case structure
done
