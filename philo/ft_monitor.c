#include "philo.h"

void	*monitor_routine(void *v_info)
{
	t_info	*info = (t_info *)v_info;
	int		i;
	double	base;

	while (!get_someone_die(info) && get_num_of_finish(info) < info->num_of_philo)
	{
		i = -1;
		while (++i < info->num_of_philo && get_num_of_finish(info) < info->num_of_philo)
		{
			// base = get_philo_last_eat(info, i);
			base = info->philo[i].last_eat;
			if (base == 0)
				base = info->philo[i].start_time;
			if (get_ms_time() - base > info->time_to_die)
			{
				ft_usleep(1);
				pthread_mutex_lock(&(info->die));
				info->someone_die = TRUE;
				pthread_mutex_unlock(&(info->die));
				break;
			}
			ft_usleep(0.01);
		}
		// ft_usleep(0.01);
	}
	pthread_mutex_lock(&(info->print));
	if (get_num_of_finish(info) == info->num_of_philo)
		printf("\x1b[32m%6dms   SUCCESS! Everyone finished their meal.\x1b[0m\n", (int)(get_ms_time() - info->philo[i % info->num_of_philo].start_time));
	else if (get_someone_die(info))
		printf("\x1b[31m%6dms   Philosopher %-3d  died\x1b[0m\n", (int)(get_ms_time() - info->philo[i].start_time), info->philo[i].idx);
	pthread_mutex_unlock(&(info->print));
	return ((void *)0);
}
