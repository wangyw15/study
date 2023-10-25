#!/bin/bash

if [ -d cppdir ]
then
    echo "cppdir is a directory"
else
    echo "cppdir is not a directory"
fi

if [ -f filea ]
then
    echo "filea is a regular file"
else
    echo "filea is not a regular file"
fi

if [ -r filea ]
then
    echo "filea has read permission"
else
    echo "filea doest not have read permission"
fi

if [ -w filea ]
then
    echo "filea has write permission"
else
    echo "filea doest not have write permission"
fi

if [ -x cppdir ]
then
    echo "cppdir has execute permission"
else
    echo "cppdir doest not have execute permission"
fi

