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
	# mv libft/libft.a .
	$(CC) $(INC) -o $(NAME) $(OBJ) $(LIBS)
	# $(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)


all: $(NAME)

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f libft.a
	rm -f $(NAME)

re: fclean all 


# LIBFT	=	libft
# HEADERS	=	headers
# DEPS	=	$(shell find $(HEADERS) -name *.h)
# INCLUDES	= -I $(HEADERS) -I $(LIBFT)
# LIBS	=	-L./$(LIBFT) -lft
# $(NAME):	$(DEPS) $(OBJS)
# 			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
# 			printf "$(WHT)[$(GRN)$(NAME) COMPILED$(WHT)]\n"

# all:		$(NAME)

# bonus:		$(DEPS) $(BONUS_OBJS)
# 			@make $(FAST)bonus -C $(LIBFT)
# 			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(BONUS_OBJS) $(LIBS)
# 			printf "$(WHT)[$(GRN)$(NAME) BONUS COMPILED$(WHT)]\n"

# miniclean:
# 			$(RM) $(OBJS)
# 			$(RM) $(BONUS_OBJS)
# 			printf "$(WHT)[$(YEL)$(NAME) OBJS REMOVED$(WHT)]\n"

# clean:		miniclean
# 			@make clean -C $(LIBFT)

# fclean:		miniclean
# 			$(RM) $(NAME)
# 			@make fclean -C $(LIBFT)
# 			printf "$(WHT)[$(YEL)$(NAME) BINARIES REMOVED$(WHT)]\n"

# re:			fclean all

# .PHONY:		all bonus miniclean clean fclean re