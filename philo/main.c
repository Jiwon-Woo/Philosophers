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

	if ((philo->idx + 1) % 2)
	{
		pthread_mutex_lock(philo->rfork);
		printf("Philosopher %d holds the right fork.\n", philo->idx + 1);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(philo->lfork);
		printf("Philosopher %d holds the left fork.\n", philo->idx + 1);
	}
	if ((philo->idx + 1) % 2)
	{
		pthread_mutex_lock(philo->lfork);
		printf("Philosopher %d holds all fork.\n", philo->idx + 1);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		printf("Philosopher %d holds all fork.\n", philo->idx + 1);
	}
	printf("%dms Philosopher %d is eating...\n", (int)(get_ms_time() - philo->start_time), philo->idx + 1);
	philo->last_eat = get_ms_time();
	usleep(1500000);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	printf("%dms Philosopher %d is finish eating!\n", (int)(get_ms_time() - philo->start_time), philo->idx + 1);
	return ((void *)0);
}

double	get_ms_time()
{
	struct timeval	time;
	double			time_ms;

	gettimeofday(&time, 0);
	time_ms = time.tv_sec * 1000 + ((double)time.tv_usec / 1000);	// 총 초가 흘렀는지 계산
	// printf("time_ms : %f\n", time_ms);
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
	}
	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(info->philo[i].id, NULL);
	i = -1;
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->lock));
	return (0);
}
