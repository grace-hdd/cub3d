
NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -Iinc -I$(LIBFT_DIR) -I$(MLX_DIR)

LDFLAGS = $(LIBFT) $(MLX) -lXext -lX11 -lm

HEADERS = inc/cub3d.h

SRCS = main.c \
	parsing/check_args.c parsing/read_file.c parsing/parse_texture.c \
	parsing/parse_color.c parsing/parse_elements.c parsing/parse_utils.c \
	parsing/parse_map.c parsing/parse_player.c parsing/parse_element_checks.c \
	render/player_view.c \
	utils/error.c utils/get_next_line.c utils/get_next_line_utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR) CC="cc -std=gnu17"

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
