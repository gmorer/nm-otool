# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 17:10:31 by gmorer            #+#    #+#              #
#    Updated: 2018/01/18 17:44:14 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
NAME= ft_otool
FLAG= -Werror -Wextra -Wall
CPATH= src/
OPATH= obj/
HPATH= inc/
INC= $(addprefix -I, $(HPATH))
CFILES= main.c
HFILES= inc/otool.h
OFILES= $(CFILES:.c=.o)
OBJ= $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean name re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
