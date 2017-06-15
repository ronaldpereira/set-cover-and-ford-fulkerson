all:
	gcc -Wall -Wextra -g ford.c -o ford.exe

run:
	./ford.exe ../../tests/testford/input.txt ../../tests/testford/output.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean
