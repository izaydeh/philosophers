NAME = philo

SRCS = src/main.c src/routine.c src/monitor.c src/utils1.c src/utils2.c
OBJ_DIR = obj
OBJ = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
INC = -I./inc
LINK = -lpthread #-fsanitize=thread

RED = \033[0;38;5;160m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LINK)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[CLEAN] Object files removed 🧼$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEAN] Executable removed 💥$(RESET)"

re: fclean all

.PHONY: all clean fclean re
