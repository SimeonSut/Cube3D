NAME = cub3D
CC = cc
FLAGS = -Werror -Wall -Wextra -g

PARSER_PATH = src/parser/
RENDER_PATH = src/render/

SRC_PARSER = parser.c parser_tools.c parser_map.c parser_player.c
SRC_RENDER = render.c

SRCS = 	src/main.c \
		$(addprefix $(PARSER_PATH), $(SRC_PARSER)) \
		$(addprefix $(RENDER_PATH), $(SRC_RENDER))

OBJ = $(SRCS:.c=.o)

GNL_PATH = get_next_line/
GNL = get_next_line/gnl.a

LIBFT_PATH = libft/
LIBFT = libft/libft.a

INC = -I ./includes/ -Ilibft

all:$(NAME)

$(NAME):$(OBJ) $(GNL) $(LIBFT)
	$(CC) $(FLAGS) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c 
	$(CC) $(FLAGS) $(INC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

mlx:
	make -C mlx_linux/

$(LIBFT):
	make -C $(LIBFT_PATH)

$(GNL):
	make -C $(GNL_PATH)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_PATH)
	make clean -C $(GNL_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(GNL_PATH)

re: fclean all

.PHONY:all clean fclean re