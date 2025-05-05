symnmf: array_2d.o datapoint_file.o matrix.o symnmflib.o symnmf.o
	@echo "Building symnmf"
	@gcc -o symnmf matrix.o array_2d.o datapoint_file.o symnmflib.o symnmf.o -lm
	@rm -f *.o

symnmf.o: symnmflib.o array_2d.o datapoint_file.o
	@gcc -ansi -Wall -Wextra -Werror -pedantic-errors -c symnmf.c

symnmflib.o: array_2d.o matrix.o
	@gcc -ansi -Wall -Wextra -Werror -pedantic-errors -c symnmflib.c

matrix.o: array_2d.o
	@gcc -ansi -Wall -Wextra -Werror -pedantic-errors -c matrix.c

array_2d.o:
	@gcc -ansi -Wall -Wextra -Werror -pedantic-errors -c array_2d.c

datapoint_file.o:
	@gcc -ansi -Wall -Wextra -Werror -pedantic-errors -c datapoint_file.c

