NAME = philo
LIB = libphilo.a
CFLAGS = -Wall -Wextra -Werror
LFLAG = -L. -lphilo
SOURCE = ft_utils.c \
	ft_atoi.c \
	ft_init.c \
	ft_valid.c 
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