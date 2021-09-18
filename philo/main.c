#include "philo.h"

// void	*sub_routine(void *v_philo)
// {
// 	t_philo *philo = (t_philo *)v_philo;

// 	pthread_mutex_lock(&(philo->info->lock));
// 	printf("==============\n");
// 	printf("philo_idx : %d\n", philo->idx);
// 	printf("philo_id : %u\n", (unsigned int)philo->id);
// 	printf("right_fork_idx : %d\n", philo->rfork_idx);
// 	printf("left_fork_idx : %d\n", philo->lfork_idx);
// 	printf("==============\n");
// 	pthread_mutex_unlock(&(philo->info->lock));
// 	return ((void *)0);
// }

void	*routine(void *v_philo)
{
	t_philo *philo = (t_philo *)v_philo;
	int	must_eat = philo->info->num_of_each_must_eat;

	if ((philo->idx) % 2 == 0)
	{
		ft_usleep(50);
	}
	int num = -1;
	if (must_eat <= 0)
		must_eat = 5;
	while (++num < must_eat)
	{
		if ((philo->idx) % 2)
		{
			pthread_mutex_lock(philo->rfork);
			philo->state = RFORK;
			ft_print_status(philo, "has taken a right fork.");
			pthread_mutex_lock(philo->lfork);
			philo->state = LFORK;
		}
		else
		{
			pthread_mutex_lock(philo->lfork);
			philo->state = LFORK;
			ft_print_status(philo, "has taken a left fork.");
			pthread_mutex_lock(philo->rfork);
			philo->state = RFORK;
		}
		// pthread_mutex_lock(&(philo->info->lock));
		philo->state = EAT;
		philo->count_eat++;
		ft_print_status(philo, "is eating.");
		philo->last_eat = get_ms_time();
		// pthread_mutex_unlock(&(philo->info->lock));
		ft_usleep(philo->info->time_to_eat);
		philo->state = SLEEP;
		ft_print_status(philo, "is sleeping.");
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		ft_usleep(philo->info->time_to_sleep);
		pthread_mutex_lock(&(philo->info->thinking));
		if (philo->info->philo[philo->lphilo].state == RFORK ||
			philo->info->philo[philo->rphilo].state == LFORK ||
			philo->info->philo[philo->lphilo].state == EAT ||
			philo->info->philo[philo->rphilo].state == EAT)
		{
			philo->state = THINK;
			ft_print_status(philo, "is thinking.");
		}
		pthread_mutex_unlock(&(philo->info->thinking));
	}
	return ((void *)0);
}

double	get_ms_time()
{
	struct timeval	time;
	double			time_ms;

	gettimeofday(&time, 0);
	time_ms = time.tv_sec * 1000 + ((double)time.tv_usec / 1000);	// 총 몇 밀리초가 흘렀는지 계산
	return (time_ms);
}

int	main(int argc, char **argv)
{
	int		*arg;
	t_info	*info;
	int		i;

	arg = is_valid_arg(argc, argv);
	if (arg == 0)
		return (ft_error("Argument Error\n"));
	info = init_info(arg);
	free(arg);
	arg = 0;
	if (info == 0)
		return (ft_error("Malloc Error\n"));
	i = -1;
	while (++i < info->num_of_philo)
	{
		pthread_create(&(info->philo[i].id), NULL, routine, (void *)(&info->philo[i]));
		// ft_usleep(100);
	}
	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(info->philo[i].id, NULL);
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->lock));
	return (0);
}
