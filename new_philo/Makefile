MAKEFLAGS += --quiet

CC = gcc -Wall -Werror -Wextra -fsanitize=address -g

SRC = $(wildcard src/*.c)

LIBFT = Libft/includes

HEADERS = includes

DEPS = $(shell find $(HEADERS) -name *.h)

INC = -I $(HEADERS) -I $(LIBFT)

LIBS = -L./Libft -lft

NAME = philo

OBJ = $(SRC:%.c=%.o)

%.o : %.c
	$(CC) $(INC) -o $@ -c $<
	
$(NAME): $(DEPS) $(OBJ)
	$(MAKE) -C Libft
	$(CC) $(INC) -o $(NAME) $(OBJ) $(LIBS)

all: $(NAME)

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f libft.a
	rm -f $(NAME)

re: fclean all 
