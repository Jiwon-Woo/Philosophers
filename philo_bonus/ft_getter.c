#include "philo_bonus.h"

int	get_num_of_finish(t_info *info)
{
	sem_wait((info->finish));
	sem_post((info->finish));
	return (info->num_of_finish);
}

int	get_someone_die(t_info *info)
{
	sem_wait((info->die));
	sem_post((info->die));
	return (info->someone_die);
}
