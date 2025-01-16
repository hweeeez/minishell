# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Libraries and includes
LIBFT = libft/libft.a
LIBFT_DIR = libft
INC_DIR = inc
INC = -I$(INC_DIR) -I$(LIBFT_DIR)
READLINE = -lreadline

# Header files
HEADERS = $(INC_DIR)/minishell.h \
          $(INC_DIR)/token.h \
          $(INC_DIR)/parse.h \
          $(INC_DIR)/exec.h \
          $(INC_DIR)/pipe.h \
          $(INC_DIR)/redirect.h \
          $(INC_DIR)/builtins.h \
          $(INC_DIR)/heredoc.h \
          $(INC_DIR)/signal.h \
          $(INC_DIR)/error.h \
		  $(INC_DIR)/expansion.h \
		  $(INC_DIR)/env.h

# Directories
OBJ_DIR = obj
SRC_DIRS = token parse exec pipe redirect builtins heredoc signal error expansion env

# Source files (separate main.c)
SRCS = $(wildcard $(SRC_DIRS:=/*.c))
MAIN_SRC = main.c

# Object files (separate main.o)
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o

# Create obj directories string for creation
OBJ_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SRC_DIRS))

# Rules
all: $(NAME)

# Create object directories
$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Special rule for main.c
$(MAIN_OBJ): $(MAIN_SRC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Compile other object files
# This line makes every .o file depend on ALL headers $(OBJ_DIR)/%.o: %.c  #$(HEADERS)
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

## HEADERS = $(INC_DIR)/minishell.h  #replace with this line when minshell.h is set up

# Link program
$(NAME): $(LIBFT) $(OBJ_DIRS) $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) $(READLINE) -o $(NAME)

# Clean object files
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Remake everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
