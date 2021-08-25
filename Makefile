CC = gcc -Wall -Werror -Wextra

UNAME := $(shell uname)

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

NAME = philo


$(NAME): $(OBJ)
	ifeq ($(UNAME), Linux)
		$(CC) $(OBJ) -lpthread -o $@
	endif
	ifeq ($(UNAME), macOs)
		$(CC) $(OBJ) -o $@
	endif

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean all
