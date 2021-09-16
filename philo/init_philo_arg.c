#include "philo.h"

int	*init_philo_arg(int argc, char **argv)
{
	int	i;
	int	*philo;

	philo = 0;
	if (!(argc == 5 || argc == 6))
		return (0);
	i = 0;
	philo = (int *)malloc(sizeof(int) * argc);
	memset(philo, -1, sizeof(int) * argc);
	philo[0] = argc - 1;
	while (++i < argc)
		atoi_ret_err(argv[i], &philo[i]);
	i = -1;
	while (++i < argc)
	{
		if (philo[i] < 0)
		{
			free(philo);
			philo = 0;
			return (0);
		}
	}
	return (philo);
}

t_philo_info	*free_philo_info(t_philo_info *philo_info)
{
	if (philo_info->philo_arg)
		free(philo_info->philo_arg);
	if (philo_info->philosophers)
		free(philo_info->philosophers);
	if (philo_info->forks)
		free(philo_info->forks);
	philo_info->philosophers = 0;
	philo_info->forks = 0;
	philo_info->philo_arg = 0;
	free(philo_info);
	return (0);
}

// t_philo	*init_philo(t_philo_info *philo_info)
// {
// 	t_philo	*philo;
// 	int		i;

// 	if (philo_info == 0)
// 		return (0);
// 	philo = malloc(sizeof(t_philo) * philo_info->philo_arg[NUM_OF_PHILO]);
// 	if (philo == 0)
// 		return (0);
// 	i = -1;
// 	while (++i < philo_info->philo_arg[NUM_OF_PHILO])
// 	{
// 		philo[i].philo_id = philo_info->philosophers[i];
// 		philo[i].right_fork = philo_info->forks[i];
// 		if (i + 1 == philo_info->philo_arg[NUM_OF_PHILO])
// 			philo[i].left_fork = philo_info->forks[0];
// 		else
// 			philo[i].left_fork = philo_info->forks[i + 1];
// 	}
// 	return (philo);
// }

void	*start_routine(void *philo_info)
{
	static int		index;
	t_philo_info	*pi;

	pi = (t_philo_info *)philo_info;
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

int	create_philosophers(t_philo_info *philo_info)
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

int	create_forks(t_philo_info *philo_info)
{
	int	i;
	int j;

	i = -1;
	while (++i < philo_info->philo_arg[NUM_OF_PHILO])
	{
		if (pthread_mutex_init(&(philo_info->forks[i]), NULL) < 0)
		{
			j = -1;
			while (++j < i)
			{
				//
				pthread_mutex_destroy(&(philo_info->forks[j]));
			}
			return (0);
		}
	}
	return (1);
}

t_philo_info	*init_philo_info(int *philo_arg)
{
	t_philo_info	*philo_info;

	philo_info = malloc(sizeof(t_philo_info));
	if (philo_info == 0)
		return (0);
	philo_info->philo_arg = philo_arg;
	philo_info->philosophers = (pthread_t *)malloc(\
		sizeof(pthread_t) * philo_arg[NUM_OF_PHILO]);
	philo_info->forks = (pthread_mutex_t *)malloc(\
		sizeof(pthread_mutex_t) * philo_arg[NUM_OF_PHILO]);
	if (philo_info->philosophers == 0 || philo_info->forks == 0)
		return (free_philo_info(philo_info));
	if (!create_forks(philo_info))
		return (free_philo_info(philo_info));
	if (!create_philosophers(philo_info))
		return (free_philo_info(philo_info));
	return (philo_info);
}

