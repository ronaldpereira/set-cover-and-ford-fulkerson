all:
	gcc -Wall -Wextra -g ford.c -o ford.exe

run:
	./ford.exe ../../test/testford/input.txt ../../test/testford/output.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean
