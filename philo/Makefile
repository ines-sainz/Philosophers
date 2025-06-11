# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/15 09:40:58 by isainz-r          #+#    #+#              #
#    Updated: 2024/10/15 09:41:01 by isainz-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final executable for the main program
NAME	=	philo

# Compiler to use
CC		=	gcc

# Compiler flags: warnings, debugging info (optional: sanitize)
CFLAGS	=	-Wall -Werror -Wextra -O0 #-g3 -fsanitize=thread #-fsanitize=leak

# Source files for the main program
SRCS	=	main.c \
			parse.c \
			set_table.c \
			libft.c \
			threads.c \
			actions.c \
			death.c

# Object files generated from main sources
OBJS	=	$(SRCS:.c=.o)

# Default target: builds the main executable
all: $(NAME)

# Rule to link object files and produce the main executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread	# Link everything

# Removes object files (main and bonus)
clean:
	rm -f $(OBJS)	# Remove main object files

# Cleans all generated files including executables
fclean: clean
	rm -f $(NAME)	# Remove main executable

# Rebuild everything from scratch
re: fclean all

# Declare non-file targets to prevent make from getting confused
.PHONY: clean fclean re all
