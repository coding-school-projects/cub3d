# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 23:22:27 by pchennia          #+#    #+#              #
#    Updated: 2024/11/07 13:48:39 by olmohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

BONUS		= .bonus

SRCS 		= src/main.c src/rendering/key.c src/rendering/movement.c \
			  src/rendering/ray.c src/rendering/screen.c \
			  src/parsing/color_parser.c src/parsing/map_parser.c \
			  src/parsing/memory_management.c src/parsing/parsing.c \
			  src/parsing/settings.c src/parsing/texture.c src/parsing/utils.c \
			  src/parsing/validate_map.c
OBJS		= $(SRCS:.c=.o)

SRCS_BONUS 	= src_bonus/main_bonus.c src_bonus/init_bonus.c \
			  src_bonus/rendering/key_bonus.c src_bonus/rendering/minimap_bonus.c\
			  src_bonus/rendering/movement_bonus.c src_bonus/rendering/ray_bonus.c \
			  src_bonus/rendering/screen_bonus.c \
			  src_bonus/parsing/color_parser_bonus.c \
			  src_bonus/parsing/map_parser_bonus.c \
			  src_bonus/parsing/memory_management_bonus.c \
			  src_bonus/parsing/parsing_bonus.c \
			  src_bonus/parsing/settings_bonus.c src_bonus/parsing/texture_bonus.c \
			  src_bonus/parsing/utils_bonus.c \
			  src_bonus/parsing/validate_map_bonus.c
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

# mlx library
MLX			= ./minilibx-linux/
MINILIBX	= minilibx-linux/libmlx.a
LFLAGS		= -L $(MLX) -l mlx -lXext -lX11

FT			= ./libft/
FT_LIB		= ./libft/libft.a

CC		  	= gcc
CFLAGS	  	= -Wall -Wextra -Werror -I./include -I $(MLX) -I $(FT) -g

GREEN=\033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

bonus: $(BONUS)

$(BONUS): $(FT_LIB) $(MINILIBX) $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) -lm $(FT_LIB) -o $(NAME) $(LFLAGS)
	@touch ${BONUS}
	@echo "$(GREEN) Created $(NAME) $(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(FT_LIB) $(MINILIBX) $(OBJS)
	$(CC) $(OBJS) -lm $(FT_LIB) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN) Created $(NAME) $(RESET)"

$(MINILIBX): FORCE
	make -C $(MLX)

$(FT_LIB): FORCE
	make -C $(FT)

FORCE:

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@make -C $(MLX) clean >/dev/null
	@make -C $(FT) clean >/dev/null
	@echo "$(YELLOW) Removed object files $(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf ${BONUS}
	@make -C $(MLX) clean >/dev/null
	@make -C $(FT) fclean >/dev/null
	@echo "$(YELLOW) Removed $(NAME) $(RESET)"

re:  fclean all
	
.PHONY: clean bonus fclean re all