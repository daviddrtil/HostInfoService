# IPK - project 1
# Brief:	Makefile to compile and build hinfosvc
# Author: 	David Drtil <xdrtil03@stud.fit.vutbr.cz>
# Date:		2022-02-20

CC=gcc
CFLAGS=-std=gnu99 -Wall
FILES=./src/*.c ./src/*.h
NAME=hinfosvc

$(NAME): $(FILES)
		$(CC) $(CFLAGS) $(FILES) -o $(NAME)

clean:
	rm -f $(NAME)

zip:
	zip xdrtil03.zip $(FILES) Makefile Readme.md
