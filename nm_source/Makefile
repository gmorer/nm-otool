# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 17:10:31 by gmorer            #+#    #+#              #
#    Updated: 2017/12/14 18:23:54 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= clang
NAME= nm
CPATH= src/
FLAG= -Weverything
OPATH= obj/
HPATH= inc/
CFILES= main.c
OFILES= $(CFILES:.c=.o)
HFILES= inc/nm.h
OBJ= $(addprefix $(OPATH), $(OFILES))
INC= $(addprefix -I, $(HPATH))

.PHONY: all clean fclean name re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(FLAG) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
