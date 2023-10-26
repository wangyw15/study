#!/bin/bash
select item in "show PATH" exit
do
    if [ "$item" = "exit" ]
    then
        break
    else
        echo $PATH
    fi
done
