#include "philo.h"

void	philo_eating(t_philo *philo)
{
	if ((philo->idx) % 2)
	{
		pthread_mutex_lock(philo->rfork);
		ft_print_status(get_ms_time(), philo, "has taken a right fork");
		pthread_mutex_lock(philo->lfork);
	}
	else
	{
		pthread_mutex_lock(philo->lfork);
		ft_print_status(get_ms_time(), philo, "has taken a left fork");
		pthread_mutex_lock(philo->rfork);
	}
	philo->count_eat++;
	pthread_mutex_lock(&(philo->info->last_meal));
	philo->last_eat = get_ms_time();
	ft_print_status(philo->last_eat, philo, "is eating");
	pthread_mutex_unlock(&(philo->info->last_meal));
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
	pthread_mutex_lock(&(philo->info->last_meal));
	philo->last_eat = get_ms_time();
	pthread_mutex_unlock(&(philo->info->last_meal));
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
	while ((++i) * 2 < info->num_of_philo)
	{
		if (pthread_create(&(info->philo[i * 2].id), NULL, \
				philo_routine, (void *)(&info->philo[i * 2])))
			return (-1);
		pthread_detach(info->philo[i * 2].id);
	}
	ft_usleep(0.1);
	i = -1;
	while ((++i) * 2 + 1 < info->num_of_philo)
	{
		if (pthread_create(&(info->philo[i * 2 + 1].id), NULL, \
				philo_routine, (void *)(&info->philo[i * 2 + 1])))
			return (-1);
		pthread_detach(info->philo[i * 2 + 1].id);
	}
	return (1);
}
