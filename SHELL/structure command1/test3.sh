#!/bin/bash
# Testing the multiple commands in the then section
#

testuser=li

if grep $testuser /etc/passwd; then
  echo "This is my first command"
  echo "This is my second command"
  ls -a /Users/$testuser/.b*
else
  echo " The user $testuser does not exist on this system."
fi
