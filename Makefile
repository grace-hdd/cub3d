# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grhaddad <grhaddad@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/02 17:22:56 by grhaddad          #+#    #+#              #
#    Updated: 2026/11/02 17:22:56 by grhaddad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -Iinclude -I$(LIBFT_DIR) -$(MLX_DIR)
LDFLAGS = $(LIBFT) $(MLX) -lXext -lX11 -lm

HEADERS = cub3d.h

SRCS		= main.c
 
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
 
all: $(NAME)
 
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
 
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
 
$(MLX):
	$(MAKE) -C $(MLX_DIR)
 
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)
 
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
 
re: fclean all
 
.PHONY: all  clean fclean re