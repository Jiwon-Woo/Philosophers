#include "philo.h"

void	*start_routine(void *philo_info)
{
	static int		index;
	t_info	*pi;

	pi = (t_info *)philo_info;
	pthread_mutex_lock(&(pi->mutex_lock));
	pi->philo[index].philo_id = pi->philosophers[index];
	pi->philo[index].right_fork = pi->forks[index];
	if (index + 1 == pi->philo_arg[NUM_OF_PHILO])
		pi->philo[index].left_fork = pi->forks[index + 1];
	else
		pi->philo[index].left_fork = pi->forks[0];
	printf("index : %d\n", index);
	printf("thread_id : %u\n", (unsigned int)pi->philo[index].philo_id);
	// printf("right_fork : %lu\n", (unsigned long)pi->philo[index].right_fork.__data);
	// printf("left_fork : %p\n", (unsigned long)pi->philo[index].left_fork);
	index++;
	pthread_mutex_unlock(&(pi->mutex_lock));
	return ((void *)0);
}

int	create_philosophers(t_info *philo_info)
{
	int	i;
	int j;

	i = -1;
	philo_info->philo = malloc(sizeof(t_philo) * philo_info->philo_arg[NUM_OF_PHILO]);
	while (++i < philo_info->philo_arg[NUM_OF_PHILO])
	{
		if (pthread_create(&(philo_info->philosophers[i]), NULL, start_routine, (void *)philo_info))
		{
			j = -1;
			while (++j < i)
			{
				//
				pthread_detach(philo_info->philosophers[j]);
			}
			return (0);
		}
		usleep(100);
		// printf("philo_info->philosophers[%d] ID : %u\n", i, (unsigned int)philo_info->philosophers[i]);
	}
	return (1);
}


