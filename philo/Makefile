# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 19:17:31 by jwoo              #+#    #+#              #
#    Updated: 2021/09/22 19:17:32 by jwoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
LIB = libphilo.a
CFLAGS = -Wall -Wextra -Werror
LFLAG = -L. -lphilo
SOURCE =  ft_atoi.c \
	ft_exit.c \
	ft_getter.c \
	ft_init.c \
	ft_utils.c \
	ft_philo.c \
	ft_monitor.c
OBJECT = $(SOURCE:.c=.o)
MAIN = main.c
HEADER = philo.h

$(NAME): $(LIB) $(MAIN)
	gcc $(MAIN) $(CFLAGS) $(LFLAG) -o $(NAME)
$(LIB): $(OBJECT)
	ar rcs $(LIB) $(OBJECT)
$(OBJECT): $(SOURCE) $(HEADER)
	gcc $(CFLAGS) -c $(SOURCE)

all : $(NAME)
clean:
	@rm -f $(OBJECT)
fclean: clean
	@rm -f $(LIB)
	@rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re