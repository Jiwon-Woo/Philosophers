#include "philo.h"

int	*is_valid_arg(int argc, char **argv)
{
	int	i;
	int	*valid_arg;

	if (!(argc == 5 || argc == 6))
		return (0);
	valid_arg = (int *)malloc(sizeof(int) * 5);
	if (valid_arg == 0)
		return (0);
	memset(valid_arg, -1, sizeof(int) * 5);
	i = 0;
	while (++i < argc)
		ft_atoi(argv[i], &valid_arg[i - 1]);
	i = -1;
	while (++i < argc - 1)
	{
		if (valid_arg[i] <= 0)
		{
			free(valid_arg);
			valid_arg = 0;
			return (0);
		}
	}
	return (valid_arg);
}
