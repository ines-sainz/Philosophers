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

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g3 #-fsanitize=address -fsanitize=leak

SRCS	=	main.c \
			parse.c \
			set_table.c \
			list_philos.c \
			list_forks.c \
			libft.c \
			threads.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
