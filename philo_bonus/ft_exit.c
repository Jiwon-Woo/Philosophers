#include "philo_bonus.h"

void	free_semaphore(t_info *info)
{
	int	error;

	error = 0;
	error += sem_close(info->forks);
	error += sem_close(info->die);
	error += sem_close(info->print);
	error += sem_close(info->finish);
	error += sem_unlink("forks");
	error += sem_unlink("die");
	error += sem_unlink("print");
	error += sem_unlink("finish");
	if (error)
		exit (1);
}

t_info	*free_info(t_info *info)
{
	if (info->philo)
		free(info->philo);
	info->philo = 0;
	free(info);
	return (0);
}

int	ft_exit(t_info *info, char *error, int exit)
{
	if (error)
		write(1, error, ft_strlen(error));
	if (info == 0)
		return (exit);
	free_semaphore(info);
	free_info(info);
	return (exit);
}
