#!/bin/bash
for filename in $1/*; do
	echo $filename
	./lem-in < $filename > output.txt
done
	

#make && ./lem-in $1