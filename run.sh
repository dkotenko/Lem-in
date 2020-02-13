#!/bin/bash
for filename in $1/*; do
	echo $filename
	./lem-in < $filename
done
	

#make && ./lem-in $1