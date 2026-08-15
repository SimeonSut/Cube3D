NAME = gnl.a
SRC = get_next_line.c
OBJ = $(SRC:.c=.o)

LIBFT_PATH = ../libft/
LIBFT = ../libft/libft.a

AR = ar rcs
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

all: $(NAME)

$(NAME):$(OBJ) $(LIBFT)
	$(AR) $@ $^

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all