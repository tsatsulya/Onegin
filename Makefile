CC=g++

debug:
	${CC} Onegin.c -DDEBUG -O0 -Og -Wall -Wextra -Werror -o debug
release:
	${CC} Onegin.c -O3 -Wall -Wextra -Werror -o release
