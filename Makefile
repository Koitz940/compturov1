NAME = computorv1
NAME_BONUS = computorv1_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC = main.c free.c get_equal_zero.c pol_ops.cs

LIBFT_DIR = libft
INCLUDE_DIR	= include
GNL_DIR = gnl
INCLUDES	= -I$(INCLUDE_DIR) \
			  -I$(LIBFT_DIR) 

OBJS = $(SRC:.c=.o)
OBJ_DIR = obj
OBJECTS	= $(addprefix $(OBJ_DIR)/, $(OBJS))


LIBFT = libft/libft.a
FLAGS =  -lft -Llibft

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $@ 

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(RM) $(OBJECTS)
	$(MAKE) clean -C libft

fclean: clean
	rm -rf $(OBJ_DIR)
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all, fclean, clean, re