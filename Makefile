NAME = philo
SRCS = src/eating.c src/init.c src/routine.c src/threads.c src/utils_thread.c src/utils.c src/main.c
OBJ_DIR = obj
OBJ = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
LINK =  -lpthread #-fsanitize=thread
INC = -I./inc
RED = \033[0;38;5;160m
GREEN = \033[0;38;5;22m
DONE = \033[1;33m
RESET = \033[0m

all: $(NAME)
	@echo "🔥 $(GREEN) Compilation done successfully 🔥$(RESET)"
	@echo "        ☠️  $(DONE) hello philo ☠️$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LINK)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[CLEAN] Object files removed 🧹$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[FCLEAN] Executable removed 🧹$(RESET)"

re: fclean all

.PHONY: all clean fclean re