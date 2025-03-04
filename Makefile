NAME = pipex
CC = cc 
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
INCLUDES = -I./inc -I./libft/
SRC_PATH = src/
OBJ_PATH = obj/

SRCS = $(SRC_PATH)/main.c \
	$(SRC_PATH)/error_handling.c \
	$(SRC_PATH)/misc.c \
	$(SRC_PATH)/path_check.c \
	$(SRC_PATH)/processes.c \

SRC	= $(addprefix $(SRC_PATH), $(SRCS))
OBJ = $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

all:	$(NAME) 

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

clean: 
	@$(MAKE) -C ./libft clean 
	@rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C ./libft fclean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
