# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 14:20:23 by rgomes-g          #+#    #+#              #
#    Updated: 2025/11/19 14:20:25 by rgomes-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

# Compilers and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCDIR)

# Directories
SRCDIR = srcs
INCDIR = includes
LIBFT_DIR = LIBFT_

# LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

# SRCS
SRCS =  $(SRCDIR)/pipex.c \
		$(SRCDIR)/is_valid_cmd.c \
		$(SRCDIR)/utils.c

# OBJS
OBJS = $(SRCS:.c=.o)

# Main rule
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -o $(NAME) $(OBJS) $(LIBFT)

# Clean object files
clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

# Full clean
fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

# Recompile everything
re: fclean all

.PHONY: fclean all clean re
