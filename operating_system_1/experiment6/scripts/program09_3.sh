#!/bin/bash
i=0
result=0
# until [ $i -ge 10 ]
# do
#     i=`expr $i + 1`
#     result=`expr $result + \( $i \* 2 \)`
# done
until (( i >= 10 ))
do
    ((i++))
    ((result += i * 2))
done
echo "result is $result"
