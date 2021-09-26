#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_info_philo(argc, argv);
	if (info == 0)
		return (ft_exit(NULL, "Error\n", 1));
	if (create_philo(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	if (create_monitor(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	return (ft_exit(info, NULL, 0));
}
