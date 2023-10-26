#!/bin/bash
i=0
result=0
# while [ $i -le 10 ]
# do
#     i=`expr $i + 1`
#     result=`expr $result + \( $i \* 2 \)`
# done
while (( i <= 10))
do
    ((i++))
    ((result += i * 2))
done
echo "result is $result"
