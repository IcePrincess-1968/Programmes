g++ -o a "[ZOJ2112]Dynamic Rankings.cpp" -Wall
for i in `seq 1 1 10`; do
	echo $i
	cp $i.in a.in
	time ./a
	diff $i.out a.out -b
done
