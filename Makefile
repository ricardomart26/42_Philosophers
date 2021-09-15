MAKEFLAGS += --quiet

CC = gcc -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)

LIBFT = libft

HEADERS = include

DEPS = $(shell find $(HEADERS) -name *.h)

INC = -I $(HEADERS) -I $(LIBFT)

LIBS = -L./$(LIBFT) -lft

NAME = philo

OBJ = $(SRC:%.c=%.o)

%.o : %.c
	$(CC) $(INC) -o $@ -c $<
	
$(NAME): $(DEPS) $(OBJ)
	$(MAKE) bonus -C libft
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
