# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 20:32:57 by myuen             #+#    #+#              #
#    Updated: 2024/09/28 16:28:37 by myuen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME = libft.a

# Source files for main part of the library
MAN_SRC = ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c ft_memmove.c\
		  ft_putendl_fd.c ft_split.c ft_striteri.c ft_strlcpy.c\
		  ft_strncmp.c ft_strtrim.c ft_toupper.c ft_bzero.c\
		  ft_isalpha.c ft_isprint.c ft_memcmp.c ft_memset.c\
		  ft_putnbr_fd.c ft_strchr.c ft_strjoin.c ft_strlen.c\
		  ft_strnstr.c ft_substr.c ft_calloc.c ft_isascii.c ft_itoa.c\
		  ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c\
		  ft_strlcat.c ft_strmapi.c ft_strrchr.c ft_tolower.c\
		  ft_isspace.c ft_iswithin.c ft_isblank.c ft_strtol.c\
		  ft_isvalid_integer_str.c ft_abs.c

# Object directory and object files
OBJ_DIR = obj
MAN_OBJ = $(MAN_SRC:%.c=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra -Werror -g

CC = cc

AR = ar rcs

RM = rm -f

# Header files (add any headers your source files include)
HEADERS = libft.h

# All Target (Build the library)
all: $(NAME)
	@echo "📚 $(NAME) created successfully!"

# Create object directory if not existing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to create object files inside obj directory
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@
	@echo "🛠️  $@ created"

# Create libft.a archive
$(NAME): $(MAN_OBJ)
	$(AR) $@ $^
	@echo "📦 Archive $(NAME) built!"

# Clean up object files
clean:
	$(RM) $(MAN_OBJ)
	@echo "🧹 OBJs files deleted!"

# Clean up object files and library, remove obj directory
fclean: clean
	$(RM) $(NAME)
	rm -rf $(OBJ_DIR)
	@echo "🗑️  $(NAME) and $(OBJ_DIR) deleted!"

# Rebuild the entire library
re: fclean all
	@echo "🔄 Rebuild complete!"

.PHONY: all clean fclean re

