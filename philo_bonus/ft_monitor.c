#include "philo_bonus.h"

void	philo_starving(t_philo *philo)
{
	double	base;

	base = philo->last_eat;
	if (base == 0)
		base = philo->start_time;
	if (get_ms_time() - base > philo->info->time_to_die)
	{
		ft_usleep(2);
		// sem_wait((philo->info->die));
		philo->info->someone_die = TRUE;
		// sem_post((info->die));
	}
}

void	*monitor_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (!(philo->info->someone_die))
	{
		philo_starving(philo);
		// ft_usleep(0.01);
	}
	if (philo->info->someone_die == TRUE)
	{
		sem_wait(philo->info->die);
		sem_wait(philo->info->print);
		printf("\x1b[31m%6dms   Philosopher %-3d  died\x1b[0m\n", \
		(int)(get_ms_time() - philo->start_time), philo->idx);
		sem_post(philo->info->print);
		// sem_post(philo->info->die);
	}
	return ((void *)(0));
}

int	create_monitor(t_philo *philo)
{
	if (pthread_create(&(philo->info->monitor), NULL, monitor_routine, (void *)(philo)))
		return (-1);
	pthread_detach(philo->info->monitor);
	return (1);
}
