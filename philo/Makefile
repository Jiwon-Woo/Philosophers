NAME = philo
LIB = libphilo.a
CFLAGS = -Wall -Wextra -Werror
LFLAG = -L. -lphilo
SOURCE = ft_strlen.c \
	ft_atoi.c \
	write_err.c \
	init_philo_arg.c
OBJECT = $(SOURCE:.c=.o)
MAIN = main.c

$(NAME): $(LIB) $(MAIN)
	gcc $(MAIN) $(CFLAGS) $(LFLAG) -o $(NAME)
$(LIB): $(OBJECT)
	ar rcs $(LIB) $(OBJECT)
$(OBJECT): $(SOURCE)
	gcc $(CFLAGS) -c $(SOURCE)

all : $(NAME)
clean:
	@rm -f $(OBJECT)
fclean: clean
	@rm -f $(LIB)
	@rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re