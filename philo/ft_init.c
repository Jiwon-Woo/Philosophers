#include "philo.h"

int	init_arg(int argc, char **argv, int *arg)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (-1);
	memset(arg, -1, sizeof(int) * 5);
	i = 0;
	while (++i < argc)
		ft_atoi(argv[i], &arg[i - 1]);
	i = -1;
	while (++i < argc - 1)
	{
		if (arg[i] <= 0)
			return (-1);
	}
	return (0);
}

void	init_option(t_info *info, int *arg)
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
	int	error;

	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(info->forks[j]));
			return (0);
		}
	}
	error = 0;
	error += pthread_mutex_init(&(info->print), NULL);
	error += pthread_mutex_init(&(info->finish), NULL);
	error += pthread_mutex_init(&(info->die), NULL);
	if (error)
		return (free_mutex(info));
	return (1);
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
		info->philo[i].rfork = &(info->forks[i]);
		info->philo[i].lfork = &(info->forks[(i + 1) % info->num_of_philo]);
		info->philo[i].info = info;
		info->philo[i].last_eat = 0;
		info->philo[i].state = 0;
		info->philo[i].count_eat = 0;
		info->philo[i].start_time = get_ms_time();
	}
}

t_info	*init_info(int argc, char **argv)
{
	t_info	*info;
	int		arg[5];

	if (init_arg(argc, argv, arg) < 0)
		return (0);
	info = (t_info *)malloc(sizeof(t_info));
	if (info == 0)
		return (0);
	info->forks = (pthread_mutex_t *)malloc(sizeof(\
				pthread_mutex_t) * arg[NUM_OF_PHILO]);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * arg[NUM_OF_PHILO]);
	if (info->philo == 0 || info->forks == 0)
		return (free_info(info));
	init_option(info, arg);
	if (!init_mutex(info))
		return (free_info(info));
	init_philo(info);
	return (info);
}
