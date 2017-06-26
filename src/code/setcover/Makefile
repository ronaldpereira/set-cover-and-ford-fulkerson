all:
	gcc -Wall -Wextra -g setcover.c -o setcover.exe

run:
	./setcover.exe ../../tests/testsetcover/input.txt ../../tests/testsetcover/output.txt
	./setcover.exe ../../tests/testsetcover/set1.txt ../../tests/testsetcover/outputset1.txt
	./setcover.exe ../../tests/testsetcover/set2.txt ../../tests/testsetcover/outputset2.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean
