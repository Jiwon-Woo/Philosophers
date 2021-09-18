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

int	ft_error(char *error_message)
{
	write(1, error_message, ft_strlen(error_message));
	return (1);
}

void	ft_print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&(philo->info->print));
	printf("%6dms Philosopher %d %s (%d/%d)\n", (int)(get_ms_time() - philo->start_time), 
			philo->idx, status, philo->count_eat, philo->info->num_of_each_must_eat);
	pthread_mutex_unlock(&(philo->info->print));
}

void	ft_usleep(double time)
{
	double start;

	start = get_ms_time();
	while (time >= get_ms_time() - start)
	{
		usleep(10);
	}
}
