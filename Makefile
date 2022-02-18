NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

CC = gcc

MINILIBX = ./mlx_linux/*.a

SRC = check_header.c check_header2.c checker.c ft_init.c ft_split.c main.c parsing.c \
	 	raycast.c utils.c move.c raycast_utils.c error.c ft_atoi.c parsing2.c utils2.c

OBJ = $(SRC:.c=.o)


.c.o: $(MINILIBX)
			gcc $(CFLAGS) -I mlx_linux -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): 	$(OBJ)
			make -C mlx_linux
			$(CC) $(CFLAGS) -I mlx_linux $(OBJ) -Lmlx_linux -lm -lmlx -lXext -lX11 -o $(NAME)

clean:
			rm -f $(OBJ)
			make -C mlx_linux clean

fclean: clean
			rm -f $(NAME)
			rm -f $(MINILIBX)

re: fclean all

x: all clean

.PHONY: all bonus clean fclean re x