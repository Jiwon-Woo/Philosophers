#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == 0)
		return (-1);
	while (str[len])
		len++;
	return (len);
}

int	ft_error(char *err_message)
{
	write(1, err_message, ft_strlen(err_message));
	return (1);
}
