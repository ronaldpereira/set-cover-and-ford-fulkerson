all:
	gcc -Wall -Wextra -g setcover.c -o setcover.exe

run:
	./setcover.exe ../../test/testsetcover/input.txt ../../test/testsetcover/output.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean
