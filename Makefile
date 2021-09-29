MAKEFLAGS += -s

CC = gcc -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)

HEADERS = include

DEPS = $(shell find $(HEADERS) -name *.h)

INC = -I $(HEADERS)

NAME = philo

OBJ = $(SRC:%.c=%.o)

%.o : %.c
	$(CC) $(INC) -o $@ -c $<
	
$(NAME): $(DEPS) $(OBJ)
	$(CC) $(INC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f libft.a
	rm -f $(NAME)

re: fclean all 
