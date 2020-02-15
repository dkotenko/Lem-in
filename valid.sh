for f in 42_lem-in_tools/maps/invalid/*; do
	echo $f;		
	valgrind --leak-check=full ./lem-in "$f" > out.txt;	
	echo '\n';
done
	
