#include "philo.h"

int	write_err(char *err_message)
{
	write(1, err_message, ft_strlen(err_message));
	return (1);
}
