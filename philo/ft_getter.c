#include "philo.h"

int	get_num_of_finish(t_info *info)
{
	pthread_mutex_lock(&(info->finish));
	pthread_mutex_unlock(&(info->finish));
	return (info->num_of_finish);
}

int	get_someone_die(t_info *info)
{
	pthread_mutex_lock(&(info->die));
	pthread_mutex_unlock(&(info->die));
	return (info->someone_die);
}
