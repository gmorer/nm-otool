# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 17:10:31 by gmorer            #+#    #+#              #
#    Updated: 2018/02/21 15:00:37 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
NAME= ft_otool
FLAG= -Werror -Wextra -Wall
CPATH= src/
OPATH= obj/
HPATH= inc/ ../libbin/inc/
CFILES= main.c \
		mach_o.c \
		fat_o.c\
		print.c
HFILES= inc/otool.h \
		../libbin/inc/libbin.h
OFILES= $(CFILES:.c=.o)
OBJ= $(addprefix $(OPATH), $(OFILES))
INC= $(addprefix -I, $(HPATH))

.PHONY: all clean fclean name re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) ../libbin/libbin.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
