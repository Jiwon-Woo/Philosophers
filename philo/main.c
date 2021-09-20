#include "philo.h"

void	*monitor_routine(void *v_info)
{
	t_info	*info = (t_info *)v_info;
	int		i;
	double	base;

	while (get_someone_die(info) == FALSE)
	{
		i = -1;
		while (++i < info->num_of_philo)
		{
			ft_usleep(0.01);
			base = info->philo[i].last_eat;
			if (base == 0)
				base = info->philo[i].start_time;
			if (get_ms_time() - info->philo[i].last_eat > info->time_to_die)
			{
				ft_usleep(1);
				pthread_mutex_lock(&(info->die));
				info->someone_die = TRUE;
				pthread_mutex_unlock(&(info->die));
				break;
			}
		}
		ft_usleep(0.01);
	}
	pthread_mutex_lock(&(info->print));
	printf("\x1b[31m%6dms   Philosopher %-3d died\x1b[0m\n", (int)(get_ms_time() - info->philo[i].start_time), info->philo[i].idx);
	pthread_mutex_unlock(&(info->print));
	return ((void *)0);
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
	create_philo(info);
	pthread_create(&(info->monitor), NULL, monitor_routine, (void *)(info));
	while (!(get_someone_die(info)) && get_num_of_finish(info) < info->num_of_philo)
		ft_usleep(0.1);
	if (get_num_of_finish(info) == info->num_of_philo)
	{
		i = -1;
		while (++i < info->num_of_philo)
			pthread_detach(info->philo[i].id);
		pthread_detach(info->monitor);
		pthread_mutex_lock(&(info->print));
		printf("\x1b[32m%6dms   SUCCESS! Everyone finished their meal.\x1b[0m\n", (int)(get_ms_time() - info->philo[0].start_time));
		pthread_mutex_unlock(&(info->print));
	}
	pthread_join(info->monitor, NULL);
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_unlock(&(info->forks[i]));
	pthread_mutex_unlock(&(info->lock));
	pthread_mutex_unlock(&(info->print));
	pthread_mutex_unlock(&(info->finish));
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->lock));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->finish));
	return (0);
}
