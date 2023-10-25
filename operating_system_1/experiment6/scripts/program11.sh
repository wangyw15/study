#!/bin/bash
echo 'working directory:' `pwd`
echo 'PATH:' $PATH
echo $1 'permission:' `ls -lh $1 | awk '{print $1}'`
