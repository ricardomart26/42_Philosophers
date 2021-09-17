# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 20:16:53 by rimartin          #+#    #+#              #
#    Updated: 2021/09/17 02:02:00 by rimartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME 	= 	libft.a

BUILD_PRINT = \e[1;34mBuilding $<\e[0m

SRC		= 	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \

SRCBON 	=  ft_lstadd_back.c \
		   ft_lstadd_front.c \
		   ft_lstclear.c \
		   ft_lstdelone.c \
		   ft_lstiter.c \
		   ft_lstlast.c \
		   ft_lstmap.c \
		   ft_lstnew.c \
		   ft_lstsize.c \

OBJ 	= $(SRC:.c=.o)

OBJBON 	= $(SRCBON:.c=.o)

CC		= gcc -Wall -Werror -Wextra -I.

HEADER	= libft.h

all		: $(NAME)

$(NAME) : $(OBJ)
			ar -rcs $@ $^
									ranlib $(NAME)

bonus	: $(OBJBON) $(OBJ)
			ar -rcs $(NAME) $(OBJBON) $(OBJ)

clean	:
			rm -f $(OBJ) $(OBJBON)

fclean	: clean
			rm -f $(NAME)

re		: fclean $(NAME)

rebonus	: fclean bonus

.PHONY: all clean bonus clean fclean re rebonus
