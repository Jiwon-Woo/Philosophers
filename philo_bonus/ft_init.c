#include "philo_bonus.h"

int	init_arg(int argc, char **argv, int *arg)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (-1);
	memset(arg, -1, sizeof(int) * 5);
	i = 0;
	while (++i < argc)
		ft_atoi(argv[i], &arg[i - 1]);
	if (arg[0] > SEM_VALUE_MAX)
		return (-1);
	i = -1;
	while (++i < argc - 1)
	{
		if (arg[i] <= 0)
			return (-1);
	}
	return (0);
}

sem_t	*init_semaphore(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
	{
		if (sem_unlink(name) < 0)
			exit (1);
		sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	}
	return (sem);
}

void	init_info(t_info *info, int *arg)
{
	info->num_of_philo = arg[NUM_OF_PHILO];
	info->time_to_die = arg[TIME_TO_DIE];
	info->time_to_eat = arg[TIME_TO_EAT];
	info->time_to_sleep = arg[TIME_TO_SLEEP];
	info->num_of_each_must_eat = arg[NUM_OF_EACH_MUST_EAT];
	info->num_of_finish = 0;
	info->someone_die = FALSE;
	info->pick = init_semaphore("pick", 1);
	info->print = init_semaphore("print", 1);
	info->finish = init_semaphore("finish", 1);
	info->die = init_semaphore("die", 1);
	info->forks = init_semaphore("forks", info->num_of_philo);
}

void	init_philo(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		info->philo[i].id = 0;
		info->philo[i].idx = i + 1;
		info->philo[i].fork = 0;
		info->philo[i].info = info;
		info->philo[i].last_eat = 0;
		info->philo[i].count_eat = 0;
		info->philo[i].start_time = get_ms_time();
	}
}

t_info	*init_info_philo(int argc, char **argv)
{
	t_info	*info;
	int		arg[5];

	if (init_arg(argc, argv, arg) < 0)
		return (0);
	info = (t_info *)malloc(sizeof(t_info));
	if (info == 0)
		return (0);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * arg[NUM_OF_PHILO]);
	if (info->philo == 0)
		return (free_info(info));
	init_info(info, arg);
	init_philo(info);
	return (info);
}
