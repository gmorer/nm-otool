# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 17:10:31 by gmorer            #+#    #+#              #
#    Updated: 2017/12/14 17:54:47 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM_PATH= nm_source
OTOOL_PATH= otool_source
NM= nm
OTOOL= otool

.PHONY: all clean fclean re nm otool

all: nm otool

nm:
	make -C $(NM_PATH)
	cp $(NM_PATH)/$(NM) .

otool:
	make -C $(OTOOL_PATH)
	cp $(OTOOL_PATH)/$(OTOOL) .

clean:
	make clean -C $(NM_PATH)
	make clean -C $(OTOOL_PATH)

fclean: clean
	make fclean -C $(NM_PATH)
	make fclean -C $(OTOOL_PATH)
	rm $(NM)
	rm $(OTOOL)

re: fclean all
