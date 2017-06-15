all:
	gcc -Wall -Wextra -g setcover.c -lm -o setcover.exe

run:
	./setcover.exe ../test/input.txt ../test/output.txt

clean:
	rm -rf *.exe

test:
	make all && make run && make clean

gdb:
	make all && gdb setcover.exe
	# run ../test/input.txt ../test/output.txt
