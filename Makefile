NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
MLXFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm
INCLUDES = -I. -Iminilibx-linux

SRCS = main.c \
       utils.c \
       fractol.c \
       events.c

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re