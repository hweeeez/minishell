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
          $(INC_DIR)/parser.h \
          $(INC_DIR)/exec.h \
          $(INC_DIR)/pipe.h \
          $(INC_DIR)/redirect.h \
          $(INC_DIR)/builtins.h \
          $(INC_DIR)/heredoc.h \
          $(INC_DIR)/error.h \
		  $(INC_DIR)/expansion.h \
		  $(INC_DIR)/env.h

# Directories
OBJ_DIR = obj
SRC_DIRS = token parse exec pipe redirect builtins heredoc signal error expansion env

# Source files (separate main.c)
#SRCS = $(wildcard $(SRC_DIRS:=/*.c))
SRCS =	builtins/ft_cd_utils.c builtins/ft_cd.c builtins/ft_dot.c builtins/ft_dotdot.c builtins/ft_echo.c \
		builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c builtins/ft_isbulitin.c builtins/ft_pwd.c \
		builtins/ft_unset.c \
		env/check_file_access.c env/check_file_type.c env/env_utils.c env/init_shell.c env/update_env.c \
		error/error.c \
		exec/exe_builtin_helper.c exec/exe_utils_2.c exec/exe_utils.c exec/execute.c exec/ft_heredoc_utils.c exec/ft_heredoc.c \
		expansion/expansion_utils.c expansion/expansion.c expansion/here_doc_expand_utils.c expansion/here_doc_expand.c \
		parse/createtree.c parse/direxists.c parse/ft_handle_direct_path.c parse/ft_path.c parse/parse_error_utils.c \
		parse/parse_utils.c parse/redir_utils.c parse/treehelper.c \
		signal/signal_utils.c signal/signal.c \
		token/add_quote.c token/llist_utils.c token/process_no_quote.c token/process_quote.c token/process_special_tok.c \
		token/split_node_helper.c token/split_node.c token/token_helper.c token/token_syntax.c token/token_utils.c \
		token/token_utils2.c token/tokenizer.c

MAIN_SRC = main.c

# Object files (separate main.o)
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o

# Add this near the top with other variable definitions
DEPS = $(OBJS:.o=.d) $(MAIN_OBJ:.o=.d)

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
# $(MAIN_OBJ): $(MAIN_SRC)
# 	mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(INC) -g -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC) $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -MP -g -c $< -o $@

# Compile other object files
# This line makes every .o file depend on ALL headers $(OBJ_DIR)/%.o: %.c  #$(HEADERS)
# $(OBJ_DIR)/%.o: %.c
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(INC) -c -g $< -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c -g $< -o $@

## HEADERS = $(INC_DIR)/minishell.h  #replace with this line when minshell.h is set up

# Link program
# $(NAME): $(LIBFT) $(OBJ_DIRS) $(OBJS) $(MAIN_OBJ)
# 	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) $(READLINE) -g -o $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) $(READLINE) -g -o $(NAME)

# Include generated dependency files
-include $(DEPS)

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
