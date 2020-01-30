#!/bin/bash
for filename in $1/*; do
	echo $filename
	./checker.sh ../lem-in $filename
done
	

#make && ./lem-in $1
