NAME = computorv1
NAME_BONUS = computorv1_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

SRC 		= main.c free.c get_equal_zero.c pol_ops.c show.c tree.c print.c \
			get_token.c error.c create_nodes.c
SRC_DIR 	= src
SRCS 		= $(addprefix $(SRC_DIR)/, $(SRC))

SRC_BONUS 	= parsing.c str.c main.c free.c get_equal_zero.c pol_ops.c show.c tree.c print.c \
			get_token.c error.c create_nodes.c
SRC_DIR_BONUS = src_bonus
SRCS_BONUS 	= $(addprefix $(SRC_DIR_BONUS)/, $(SRC_BONUS))

LIBFT_DIR 	= libft
INCLUDE_DIR	= include
GNL_DIR 	= gnl
INCLUDES	= -I$(INCLUDE_DIR) \
			  -I$(LIBFT_DIR) 

OBJ_DIR	= obj
OBJ_BONUS_DIR = obj_bonus
OBJECTS       = $(patsubst src/%.c,obj/%.o,$(SRCS))
OBJECTS_BONUS = $(patsubst src_bonus/%.c,obj_bonus/%.o,$(SRCS_BONUS))



LIBFT = libft/libft.a
FLAGS =  -lft -Llibft

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

obj_bonus/%.o: src_bonus/%.c
	@mkdir -p obj_bonus
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lm -o $@
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(NAME_BONUS): $(LIBFT) $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(LIBFT) -lm -o $@

all: $(NAME)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJECTS) $(OBJECTS_BONUS)
	$(MAKE) clean -C libft

fclean: clean
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all, fclean, clean, re, bonus