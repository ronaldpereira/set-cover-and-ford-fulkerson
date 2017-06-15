all:
	gcc -Wall -Wextra -g setcover.c -lm -o setcover.exe && gcc -Wall -Wextra -g ford.c -lm -o ford.exe

runsetcover:
	./setcover.exe ../testsetcover/input.txt ../testsetcover/output.txt

runford:
	./ford.exe ../ford/input.txt ../ford/output.txt

clean:
	rm -rf *.exe

testsetcover:
	make all && make runsetcover && make clean

testford:
	make all && make runford && make clean

gdbsetcover:
	make all && gdb setcover.exe
	# run ../testsetcover/input.txt ../testsetcover/output.txt

gdbford:
	make all && gdb ford.exe
	# run ../ford/input.txt ../ford/output.txt
