# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 17:10:31 by gmorer            #+#    #+#              #
#    Updated: 2018/01/17 16:21:17 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
NAME= ft_nm
CPATH= src/
FLAG= -Wall -Werror -Wextra
OPATH= obj/
HPATH= inc/ ../libbin/inc/
CFILES= main.c \
		mach_o.c \
		sort.c \
		print.c \
		list.c \
		fat_mach.c
OFILES= $(CFILES:.c=.o)
HFILES= inc/nm.h\
		../libbin/inc/libbin.h
OBJ= $(addprefix $(OPATH), $(OFILES))
INC= $(addprefix -I, $(HPATH))

.PHONY: all clean fclean name re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) ../libbin/libbin.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) -g $(FLAG) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
