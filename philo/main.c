#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_info(argc, argv);
	if (info == 0)
		return (ft_error("Error\n"));
	if (create_philo(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	ft_usleep(0.1);
	if (pthread_create(&(info->monitor), NULL, monitor_routine, (void *)(info)))
		return (ft_exit(info, "Error\n", 1));
	pthread_join(info->monitor, NULL);
	return (ft_exit(info, NULL, 0));
}
