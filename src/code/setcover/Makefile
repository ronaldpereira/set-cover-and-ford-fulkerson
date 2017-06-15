all:
	gcc -Wall -Wextra -g setcover.c -o setcover.exe

run:
	./setcover.exe ../../tests/testsetcover/input.txt ../../tests/testsetcover/output.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean
