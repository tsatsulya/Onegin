CC=g++
###
debug:
	${CC} Onegin.c source/work_with_files.c source/work_with_strings.c source/utilities.c -DDEBUG -O0 -Og -Wall -Wextra -Werror -o debug
release:
	${CC} Onegin.c source/work_with_files.c source/work_with_strings.c source/utilities.c -O3 -Wall -Wextra -Werror -o release
