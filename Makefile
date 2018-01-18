# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 17:10:31 by gmorer            #+#    #+#              #
#    Updated: 2018/01/18 17:43:44 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM_PATH= nm_source
OTOOL_PATH= otool_source
LIBBIN_PATH= libbin
NM= ft_nm
OTOOL= ft_otool

.PHONY: all clean fclean re nm otool

all: nm otool

nm:
	make -C libbin
	make -C $(NM_PATH)
	cp $(NM_PATH)/$(NM) .

otool:
	make -C libbin
	make -C $(OTOOL_PATH)
	cp $(OTOOL_PATH)/$(OTOOL) .

clean:
	make clean -C $(NM_PATH)
	make clean -C $(OTOOL_PATH)
	make clean -C $(LIBBIN_PATH)

fclean: clean
	make fclean -C $(NM_PATH)
	make fclean -C $(OTOOL_PATH)
	make fclean -C $(LIBBIN_PATH)
	rm -f $(NM)
	rm -f $(OTOOL)

re: fclean all
