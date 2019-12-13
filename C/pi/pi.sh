#!/bin/bash

base=9999999

count=10

tool=./pi

start=$(date +%s)

for((i=1;i<=$count;i++))
do
	$tool `expr $base \* $i \* $i`
done

end=$(date +%s)
take=$(( end - start ))
echo Time taken to execute commands is ${take} seconds.
