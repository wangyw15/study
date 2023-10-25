#!/bin/bash
# name display program

read -p "Enter name: " input

if [ -z $input ]
then
    echo "Name not provided"
else
    echo "Your name is" $input
fi

