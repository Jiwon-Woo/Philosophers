#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_info(argc, argv);
	if (info == 0)
		return (ft_error("Error\n"));
	if (create_philo(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	if (create_monitor(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	return (0);
}
