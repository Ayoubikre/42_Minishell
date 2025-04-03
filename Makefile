CC = gcc
# CFLAGS = -Wall -Werror -Wextra -I./readline/include
CFLAGS = -Wall -I./readline/include
RDFLAGS = -L./readline/lib -lreadline

SRC = main.c
OBJC = $(SRC:%.c=%.o)

libft_Dir = ./42_libft
libft = $(libft_Dir)/libft.a

NAME = a

all: $(NAME)

$(NAME): $(OBJC)
#	make -C $(libft_Dir)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME) $(libft) $(RDFLAGS)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#	make -C $(libft_Dir) clean
	rm -rf $(OBJC) 

fclean: clean
#	make -C $(libft_Dir) fclean
	rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re