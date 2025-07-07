all:
	gcc -Wall -Wextra -Wpedantic -Werror -g -O0 -I./lib/kout -I./lib/kbg -I./lib/kbool -I./lib/kstr -I./lib/kerr main.c -o ./temp/main; ./temp/main;
