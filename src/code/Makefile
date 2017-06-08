all:
	gcc -Wall -Wextra -g tp2po.c -lm -o tp2po.exe

run:
	./tp2po.exe ../test/input.txt ../test/output.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean
