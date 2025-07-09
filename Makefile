
SAFETY_FLAGS = -Wall -Wextra -Wpedantic -Werror -g -O0
INCLUDE = -I./lib/kdefault -I./lib/kout -I./lib/kbg -I./lib/kbool -I./lib/kstr -I./lib/kerr
ENTRYPOINT = main.c
BINOUT = ./temp/main

build-min:
	gcc $(INCLUDE) main.c -o ./temp/main; ./temp/main;


build:
	gcc $(SAFETY_FLAGS) $(INCLUDE) $(ENTRYPOINT) -o $(BINOUT); ./temp/main;

run:
	./temp/main;