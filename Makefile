NAME = so_long
SOURCES = so_long.c get_next_line.c validate.c setup.c gameplay.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJECTS) minilibx libft
	gcc -o $@ $(OBJECTS) -Lminilibx_opengl_20191021 -lmlx -Llibft -lft \
		-framework OpenGL -framework AppKit -lz

%.o: %.c
	$(CC) -c $(CFLAGS) $?

minilibx:
	make -C minilibx_opengl_20191021

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C minilibx_opengl_20191021 clean
	make -C libft clean

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all bonus minilibx libft clean fclean re
