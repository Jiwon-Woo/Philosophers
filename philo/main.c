#include "philo.h"

void	*philo_routine(void *v_philo)
{
	t_philo *philo = (t_philo *)v_philo;
	int	must_eat = philo->info->num_of_each_must_eat;

	if ((philo->idx) % 2 == 0)
		ft_usleep(0.1);
	while ((must_eat == -1 || (must_eat != -1 && philo->state != FINISH)) && philo->info->exit == FALSE)
	{
		if ((philo->idx) % 2)
		{
			if (philo->info->exit == TRUE)
				break;
			pthread_mutex_lock(philo->rfork);
			philo->state = RFORK;
			ft_print_status(philo, "has taken a right fork.");
			if (philo->info->exit == TRUE)
				break;
			pthread_mutex_lock(philo->lfork);
			// philo->state = LFORK;
		}
		else
		{
			if (philo->info->exit == TRUE)
				break;
			pthread_mutex_lock(philo->lfork);
			philo->state = LFORK;
			ft_print_status(philo, "has taken a left fork.");
			if (philo->info->exit == TRUE)
				break;
			pthread_mutex_lock(philo->rfork);
			// philo->state = RFORK;
		}
		if (philo->info->exit == TRUE)
		{
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(philo->lfork);
			break;
		}
		philo->state = EAT;
		ft_print_status(philo, "is eating.");
		philo->last_eat = get_ms_time();
		philo->count_eat++;
		ft_usleep(philo->info->time_to_eat);
		if (philo->info->exit == TRUE)
		{
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(philo->lfork);
			break;
		}
		if (philo->count_eat == philo->info->num_of_each_must_eat)
		{
			philo->state = FINISH;
			philo->info->num_of_finish++;
			printf("%6dms Philosopher %d finished eating. (%d/%d)\n", (int)(get_ms_time() - philo->start_time), 
			philo->idx, philo->count_eat, philo->info->num_of_each_must_eat);
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(philo->lfork);
			break;
		}
		philo->state = SLEEP;
		ft_print_status(philo, "is sleeping.");
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		ft_usleep(philo->info->time_to_sleep);
		if (philo->info->exit == TRUE)
			break;
		pthread_mutex_lock(&(philo->info->thinking));
		if (philo->info->philo[philo->lphilo].state == RFORK ||
			philo->info->philo[philo->rphilo].state == LFORK ||
			philo->info->philo[philo->lphilo].state == EAT ||
			philo->info->philo[philo->rphilo].state == EAT)
		{
			philo->state = THINK;
			ft_print_status(philo, "is thinking.");
		}
		ft_usleep(0.05);
		pthread_mutex_unlock(&(philo->info->thinking));
	}
	return ((void *)0);
}

void	*monitor_routine(void *v_info)
{
	t_info	*info = (t_info *)v_info;
	int		i;

	pthread_mutex_lock(&(info->lock));
	while ((info->num_of_finish < info->num_of_philo) && info->exit == FALSE)
	{
		i = -1;
		while (++i < info->num_of_philo)
		{
			if (info->philo[i].last_eat == 0)
			{
				if ((get_ms_time() - info->philo[i].start_time) > info->time_to_die)
				{
					info->exit = TRUE;
					break;
				}
			}
			else
			{
				if (get_ms_time() - info->philo[i].last_eat > info->time_to_die)
				{
					info->exit = TRUE;
					break;
				}
			}
			ft_usleep(0.01);
		}
		ft_usleep(0.01);
	}
	pthread_mutex_unlock(&(info->lock));
	pthread_mutex_lock(&(info->print));
	if (info->num_of_finish == info->num_of_philo)
		printf("\x1b[32m%6dms SUCCESS! Everyone finished their meal.\x1b[0m\n", (int)(get_ms_time() - info->philo[0].start_time));
	else if (info->exit == TRUE)
		printf("\x1b[31m%6dms FAIL... SOMEONE IS DEAD.\x1b[0m\n", (int)(get_ms_time() - info->philo[0].start_time));
	pthread_mutex_unlock(&(info->print));
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_unlock(&(info->forks[i]));
	pthread_mutex_unlock(&(info->lock));
	pthread_mutex_unlock(&(info->sleeping));
	pthread_mutex_unlock(&(info->thinking));
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
	pthread_create(&(info->monitor), NULL, monitor_routine, (void *)(info));
	i = -1;
	while (++i < info->num_of_philo)
	{
		pthread_create(&(info->philo[i].id), NULL, philo_routine, (void *)(&info->philo[i]));
		ft_usleep(0.05);
	}
	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(info->philo[i].id, NULL);
	pthread_join(info->monitor, NULL);
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_unlock(&(info->forks[i]));
	pthread_mutex_unlock(&(info->lock));
	pthread_mutex_unlock(&(info->print));
	pthread_mutex_unlock(&(info->sleeping));
	pthread_mutex_unlock(&(info->thinking));
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->lock));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->sleeping));
	pthread_mutex_destroy(&(info->thinking));
	return (0);
}
