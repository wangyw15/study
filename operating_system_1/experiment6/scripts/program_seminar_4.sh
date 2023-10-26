#/bin/bash
# 1
ls -lh > filedir.txt
# 2
mkdir testdir2
# 3
cp *.c testdir2
# 4
for file in `ls testdir2/`
do
    chmod -r testdir2/$file
done
# 5
ls -lh >> filedir.txt
# 6
whoami >> filedir.txt
id >> filedir.txt
# 7
