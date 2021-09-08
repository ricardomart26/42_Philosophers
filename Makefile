CC = gcc -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)

INC = include/philo.h 

OBJ = $(SRC:.c=.o)

NAME = philo

$(NAME): $(OBJ)
	$(MAKE) bonus -C libft
	mv libft/libft.a .
	$(CC) $(OBJ) -I -L$(INC) libft.a -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f libft.a
	rm -f $(NAME)

re: fclean all
