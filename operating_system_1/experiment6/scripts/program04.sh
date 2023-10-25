#!/bin/bash
# name display program - mod

# show args
echo "Arg count:" $#
echo "Args:" $@

if [[ $# == 0 ]]
then
    echo "Name not provided"
else
    echo "Your name is" $1
fi

