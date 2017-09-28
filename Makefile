
NAME = ft_ssl

FLAGS = -Wall -Wextra -Werror

FILES = main.c base64.c base64_padding.c des.c core.c keys.c crypt_utils.c utils.c errors.c
SRCS = $(addprefix src/, $(FILES))
OBJ  = $(patsubst %.c,%.o,$(FILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -I libft/includes -I./include -L libft/ -lft $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ):
	make -C libft
	gcc -I libft/includes -I./include $(FLAGS) -c $(SRCS)

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all