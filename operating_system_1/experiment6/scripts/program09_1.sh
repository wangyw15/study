#!/bin/bash
for filename in ˋlsˋ
    do
        cp $filename backup/$filename
        if [ $? –ne 0 ]
            echo "copy $filename failed"
    fi
done
