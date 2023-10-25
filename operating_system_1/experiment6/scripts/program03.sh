#!/bin/bash
# name display program

if [[ $# == 0 ]]
then
    echo "Name not provided"
else
    echo "Your name is" $1
fi

