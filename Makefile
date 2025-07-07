all:
	gcc -Wall -Wextra -Wpedantic -Werror -g -O0 -I./lib main.c -o ./temp/main; ./temp/main;
