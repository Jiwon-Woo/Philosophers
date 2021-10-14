#include "philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->info->pick);
	sem_wait(philo->info->forks);
	ft_print_status(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	sem_post(philo->info->pick);
	philo->count_eat++;
	philo->last_eat = get_ms_time();
	ft_print_status(philo, "is eating");
	ft_usleep(philo->info->time_to_eat);
}

void	philo_sleeping_thinking(t_philo *philo)
{
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	ft_print_status(philo, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
	ft_print_status(philo, "is thinking");
	// ft_usleep(0.05);
}

int	philo_routine(t_philo *philo)
{
	create_monitor(philo);
	philo->last_eat = get_ms_time();
	while (!(philo->info->someone_die))
	{
		philo_eating(philo);
		if (philo->count_eat == philo->info->num_of_each_must_eat)
		{
			sem_post(philo->info->forks);
			sem_post(philo->info->forks);
			exit (0);
		}
		philo_sleeping_thinking(philo);
	}
	exit (1);
}

void	philo_die_or_finish(t_info *info)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	while (++i < info->num_of_philo)
	{
		waitpid((info->philo[i].id), &status, 0);
		if (!WEXITSTATUS(status))
			info->num_of_finish++;
		else
		{
			info->someone_die = TRUE;
			break ;
		}
	}
	sem_wait((info->print));
	if (info->num_of_finish == info->num_of_philo)
		printf("\x1b[32m  SUCCESS! Everyone finished their meal.\x1b[0m\n");
	else if (info->someone_die == TRUE)
	{
		j = -1;
		while (++j < info->num_of_philo)
		{
			kill(info->philo[j].id, SIGTERM);
		}
		// sem_wait(info->die);
		printf("\x1b[31m%6dms   Philosopher %-3d  died\x1b[0m\n", \
		(int)(get_ms_time() - info->philo[i].start_time), info->philo[i].idx);
		// sem_post(info->die);
	}
	sem_post((info->print));
}

int	create_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		info->philo[i].id = fork();
		if (info->philo[i].id < 0)
			exit (1);
		else if (info->philo[i].id == 0)
		{
			philo_routine(&(info->philo[i]));
		}
	}
	philo_die_or_finish(info);
	return (1);
}
