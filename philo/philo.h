#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define NUM_OF_PHILO 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define NUM_OF_EACH_MUST_EAT 5

typedef struct s_philo {
	pthread_t		philo_id;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
}	t_philo;

typedef struct s_philo_info {
	pthread_mutex_t	mutex_lock;
	int				*philo_arg;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_philo_info;

int				ft_strlen(char *str);
int				atoi_ret_err(char *str, int *integer);
int				write_err(char *err_message);
int				*init_philo_arg(int argc, char **argv);
t_philo_info	*init_philo_info(int *philo_arg);

#endif