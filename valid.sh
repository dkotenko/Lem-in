for f in 42_lem-in_tools/maps/invalid/*; do
	echo $f;		
	./lem-in "$f";	
	echo '\n';
done
	
