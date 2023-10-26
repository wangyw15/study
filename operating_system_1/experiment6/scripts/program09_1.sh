#!/bin/bash

files=`ls`

if [[ ! -d "backup" ]]
then
    mkdir backup
fi

for filename in $files
do
    cp $filename backup/
    if [[ $? -ne 0 ]]
    then
        echo "copy $filename failed"
    fi
done
