while read p; do	
	if grep -q $p 'map_big_sup_1'
	then
		echo "OK";
	else
		echo $p
	fi
done < rooms