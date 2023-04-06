# MAKEFLAGS += -s

CC = gcc

HEADERS = include

CFLAGS = -Wall -Werror -Wextra -I $(HEADERS)

SRC = $(wildcard src/*.c)


DEPS = $(shell find $(HEADERS) -name *.h)

INC = -I $(HEADERS)

NAME = philo

OBJ = $(SRC:%.c=%.o)

# %.o : %.c
# 	$(CC) $(INC) -o $@ -c $<
	
$(NAME): $(OBJ) $(DEPS) 
	$(CC) $(INC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f libft.a
	rm -f $(NAME)

re: fclean all 
