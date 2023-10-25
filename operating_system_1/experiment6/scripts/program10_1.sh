#!/bin/bash
case $1 in 
    01|1) echo "Month is January";; 
    02|2) echo "Month is February";; 
    03|3) echo "Month is March";; 
    04|4) echo "Month is April";; 
    05|5) echo "Month is May";; 
    06|6) echo "Month is June";; 
    07|7) echo "Month is July";; 
    08|8) echo "Month is August";; 
    09|9) echo "Month is September";; 
    010|10) echo "Month is October";; 
    011|11) echo "Month is November";; 
    012|12) echo "Month is December";; 
    *) echo "Invalid parameter";; 
esac
