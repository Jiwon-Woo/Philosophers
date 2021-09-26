#include "philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	if ((philo->idx) % 2)
	{
		pthread_mutex_lock(philo->rfork);
		ft_print_status(get_ms_time(), philo, "has taken a fork");
		pthread_mutex_lock(philo->lfork);
	}
	else
	{
		pthread_mutex_lock(philo->lfork);
		ft_print_status(get_ms_time(), philo, "has taken a fork");
		pthread_mutex_lock(philo->rfork);
	}
	philo->count_eat++;
	philo->last_eat = get_ms_time();
	ft_print_status(philo->last_eat, philo, "is eating");
	ft_usleep(philo->info->time_to_eat);
}

void	philo_sleeping_thinking(t_philo *philo)
{
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	ft_print_status(get_ms_time(), philo, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
	ft_print_status(get_ms_time(), philo, "is thinking");
	ft_usleep(0.05);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	philo->last_eat = get_ms_time();
	while (!get_someone_die(philo->info))
	{
		philo_eating(philo);
		if (philo->count_eat == philo->info->num_of_each_must_eat)
		{
			pthread_mutex_lock(&(philo->info->finish));
			philo->info->num_of_finish++;
			pthread_mutex_unlock(&(philo->info->finish));
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(philo->lfork);
			break ;
		}
		philo_sleeping_thinking(philo);
	}
	return ((void *)0);
}

int	create_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		info->philo[i] = fork();
		if (info->philo[i] < 0)
			exit (1);
		else if (info->philo[i] == 0)
			philo_routine(info->philo[i]);
	}
	// ft_usleep(0.1);
	return (1);
}
