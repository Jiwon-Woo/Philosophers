#include "philo.h"

int	main(int argc, char **argv)
{
	int				*philo_arg;
	t_philo_info	*philo_info;

	philo_arg = init_philo_arg(argc, argv);
	if (philo_arg == 0)
		return (write_err("Argument Error\n"));
	philo_info = init_philo_info(philo_arg);
	if (philo_info == 0)
	{
		philo_arg = 0;
		return (write_err("Malloc Error\n"));
	}
	// int i = -1;
	// while (++i < philo_arg[NUM_OF_PHILO])
	// 	printf("Philosopher[%d] ID : %u\n", i, (unsigned int)philo[i].philo_id);
	return (0);
}
