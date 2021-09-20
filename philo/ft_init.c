#include "philo.h"

t_info	*free_info(t_info *philo_info)
{
	if (philo_info->philo)
		free(philo_info->philo);
	if (philo_info->forks)
		free(philo_info->forks);
	philo_info->philo = 0;
	philo_info->forks = 0;
	free(philo_info);
	return (0);
}

void	init_philo(t_info *info)
{
	int		i;

	i = -1;
	info->num_of_finish = 0;
	info->someone_die = FALSE;
	while (++i < info->num_of_philo)
	{
		info->philo[i].id = 0;
		info->philo[i].idx = i + 1;
		if (i < 1)
			info->philo[i].rphilo = info->num_of_philo - 1;
		else
			info->philo[i].rphilo = i - 1;
		info->philo[i].lphilo = ((i + 1) % info->num_of_philo);
		info->philo[i].rfork = &(info->forks[i]);
		info->philo[i].lfork = &(info->forks[(i + 1) % info->num_of_philo]);
		info->philo[i].info = info;
		info->philo[i].last_eat = 0;
		info->philo[i].state = 0;
		info->philo[i].count_eat = 0;
		info->philo[i].start_time = get_ms_time();
	}
}

void	init_arg(t_info *info, int *arg)
{
	info->num_of_philo = arg[NUM_OF_PHILO];
	info->time_to_die = arg[TIME_TO_DIE];
	info->time_to_eat = arg[TIME_TO_EAT];
	info->time_to_sleep = arg[TIME_TO_SLEEP];
	info->num_of_each_must_eat = arg[NUM_OF_EACH_MUST_EAT];
}

int	init_mutex(t_info *info)
{
	int	i;
	int	j;

	pthread_mutex_init(&(info->lock), NULL);
	pthread_mutex_init(&(info->print), NULL);
	pthread_mutex_init(&(info->finish), NULL);
	pthread_mutex_init(&(info->die), NULL);
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) < 0)
		{
			j = -1;
			while (++j < i)
			{
				pthread_mutex_destroy(&(info->forks[j]));
			}
			return (0);
		}
	}
	return (1);
}

t_info	*init_info(int *arg)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (info == 0)
		return (0);
	info->forks = (pthread_mutex_t *)malloc(sizeof(\
				pthread_mutex_t) * arg[NUM_OF_PHILO]);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * arg[NUM_OF_PHILO]);
	if (info->philo == 0 || info->forks == 0)
		return (free_info(info));
	init_arg(info, arg);
	if (!init_mutex(info))
		return (free_info(info));
	init_philo(info);
	return (info);
}
