CC = gcc -Wall -Werror -Wextra

UNAME := $(shell uname)

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

NAME = philo


$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean all
