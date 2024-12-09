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
          $(INC_DIR)/errorcode.h

# Directories
OBJ_DIR = obj
TOKEN_DIR = token
PARSE_DIR = parse
EXEC_DIR = exec
PIPE_DIR = pipe
REDIR_DIR = redirect
BUILTIN_DIR = builtins
HEREDOC_DIR = heredoc
SIGNAL_DIR = signal
ERROR_DIR = errorcode

# Source files
SRCS = main.c \
       $(wildcard $(TOKEN_DIR)/*.c) \
       $(wildcard $(PARSE_DIR)/*.c) \
       $(wildcard $(EXEC_DIR)/*.c) \
       $(wildcard $(PIPE_DIR)/*.c) \
       $(wildcard $(REDIR_DIR)/*.c) \
       $(wildcard $(BUILTIN_DIR)/*.c) \
       $(wildcard $(HEREDOC_DIR)/*.c) \
       $(wildcard $(SIGNAL_DIR)/*.c) \
       $(wildcard $(ERROR_DIR)/*.c)

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Create obj directories string for creation
OBJ_DIRS = $(OBJ_DIR) \
           $(OBJ_DIR)/$(TOKEN_DIR) \
           $(OBJ_DIR)/$(PARSE_DIR) \
           $(OBJ_DIR)/$(EXEC_DIR) \
           $(OBJ_DIR)/$(PIPE_DIR) \
           $(OBJ_DIR)/$(REDIR_DIR) \
           $(OBJ_DIR)/$(BUILTIN_DIR) \
           $(OBJ_DIR)/$(HEREDOC_DIR) \
           $(OBJ_DIR)/$(SIGNAL_DIR) \
           $(OBJ_DIR)/$(ERROR_DIR)

# Rules
all: $(NAME)

# Create object directories
$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile object files - now with header dependencies
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Link program
$(NAME): $(LIBFT) $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
