# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 07:31:26 by dcaetano          #+#    #+#              #
#    Updated: 2025/02/15 21:01:00 by dcaetano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC             = cc
CFLAGS         = -Wall -Wextra -Werror -g -O3 #-fsanitize=address
RM             = rm -rf

OBJS_DIR       = obj/
INCLUDES_DIR   = include/

LIBFT_DIR      = libft
LIBFT_NAME     = libft.a
MINILIBX_DIR   = minilibx-linux
MINILIBX_NAME  = libmlx.a
MINILIBX_FLAGS = -g -lmlx -lXext -lX11 -lm -lz -lbsd

SRCS           = main.c src/errors.c src/exit.c src/free.c src/init.c \
                 src/init2.c src/init3.c src/game/draw_utils.c \
                 src/game/game_utils.c src/game/get_info.c \
                 src/game/hook_handler.c src/game/img_utils.c \
                 src/game/init_game.c src/game/minimap_check_1.c \
                 src/game/minimap_check_2.c src/game/minimap_check_3.c \
                 src/game/minimap_utils.c src/game/play_game.c \
                 src/game/raycast_utils.c src/game/raycast.c \
                 src/parser/config/parse_args.c \
                 src/parser/config/parse_colors.c \
                 src/parser/config/parse_config.c \
                 src/parser/config/parse_dups.c \
                 src/parser/config/parse_textures.c \
                 src/parser/config/parse_type.c \
                 src/parser/map/parse_border_utils.c \
                 src/parser/map/parse_border_utils2.c \
                 src/parser/map/parse_border_utils3.c \
                 src/parser/map/parse_border_utils4.c \
                 src/parser/map/parse_border_utils5.c \
                 src/parser/map/parse_border_utils6.c \
                 src/parser/map/parse_border_utils7.c \
                 src/parser/map/parse_border.c src/parser/map/parse_dups.c \
                 src/parser/map/parse_map.c src/parser/map/parse_player.c \
                 src/parser/parse_file.c src/parser/parse_info.c \
                 src/parser/parse_input.c src/setup/set_config.c \
                 src/setup/set_map.c src/utils/buildfree.c \
                 src/utils/display_file.c src/utils/get_lines.c \
                 src/utils/get_size.c src/utils/free.c src/utils/strcmp.c \
                 src/utils/utils1.c

OBJS           = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

EXEC           = cub3D

all: $(EXEC)

$(OBJS_DIR)%.o: %.c include/cub3D.h
	@mkdir -p $(dir $@) 2>&1 > /dev/null
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

$(OBJS_DIR)%.o: srcs/%.c include/cub3D.h
	@mkdir -p $(dir $@) 2>&1 > /dev/null
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

$(EXEC): $(OBJS)
	@make -sC $(LIBFT_DIR) 2>&1 > /dev/null
	@make -sC $(MINILIBX_DIR) 2>&1 > /dev/null
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) $^ -o $@ -L$(LIBFT_DIR) -lft -L./$(MINILIBX_DIR) $(MINILIBX_FLAGS)

clean:
	@$(RM) $(OBJS_DIR)
	@make -sC $(LIBFT_DIR) clean 2>&1 > /dev/null
	@make -sC $(MINILIBX_DIR) clean 2>&1 > /dev/null

fclean: clean
	@$(RM) $(EXEC)
	@make -sC $(LIBFT_DIR) fclean 2>&1 > /dev/null

re: fclean all

.PHONY: all clean fclean re
