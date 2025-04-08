NAME = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
MLX_PATH = minilibx-linux
LIBRARY = -L $(MLX_PATH) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX = $(MLX_PATH)/libmlx.a
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = main.c \
       utils.c \
       fractol.c \
       events.c

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft $(LIBRARY) -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

$(MLX):
	@make -s -C $(MLX_PATH) -j16 2> /dev/null

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re