CC=g++
###
debug:
	${CC} -I./header Onegin.c source/file_functions.c source/string_functions.c source/utilities.c source/sort_functions.c source/debug.c  -DDEBUG -O0 -Og -Wall -Wextra -Werror -o debug
release:
	${CC} -I./header Onegin.c source/file_functions.c source/string_functions.c source/utilities.c source/sort_functions.c source/debug.c  -O3 -Wall -Wextra -Werror -o release
