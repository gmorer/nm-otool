# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 11:36:51 by gmorer            #+#    #+#              #
#    Updated: 2018/01/17 16:15:26 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libbin.a
CC = clang
CFLAGS= -Wall -Werror -Wextra
CPATH = src/
HPATH = inc/
OPATH = obj/
CFILES =	endian.c\
			cpu_type.c

HFILES = inc/libbin.h
INC = $(addprefix -I , $(HPATH))
OBJ = $(addprefix $(OPATH), $(CFILES:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OPATH)%.o : $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(INC) $< -c -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
