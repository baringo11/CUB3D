# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 13:18:06 by jbaringo          #+#    #+#              #
#    Updated: 2020/10/14 14:25:59 by jbaringo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Werror -Wall -Wextra -g

LFLAGS = -c

GNL_FILES = GNL/get_next_line.c GNL/get_next_line_utils.c
GET_DATA_FILES = get_data/rgb.c get_data/check_map.c get_data/map_str.c get_data/read_file.c get_data/textures.c
ENGINE_FILES = engine/first_config.c engine/movement.c engine/raycast.c engine/raycast_inter.c engine/sprites.c engine/print_map.c

FILES = main.c check_error.c set_init.c utils.c bmp_file.c $(GNL_FILES) $(GET_DATA_FILES) $(ENGINE_FILES)

OBJ =  obj/*.o

all : $(NAME)

$(NAME): $(FILES)
	gcc $(CFLAGS) $(LFLAGS) $(FILES)
	mkdir -p obj
	mv *.o obj
	gcc -o $(NAME) $(OBJ) -lmlx -framework OpenGL -framework AppKit

clean :
	rm -f *.o
	rm -f obj/*.o

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re