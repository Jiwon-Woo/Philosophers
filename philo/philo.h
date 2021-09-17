#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define NUM_OF_PHILO 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUM_OF_EACH_MUST_EAT 4

typedef struct s_info t_info;
typedef struct s_philo t_philo;

typedef struct s_philo {
	int				idx;
	int				rfork_idx;
	int				lfork_idx;
	pthread_t		id;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	double			last_eat;
	double			start_time;
	t_info			*info;
}	t_philo;

typedef struct s_info {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_each_must_eat;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_mutex_t	lock;
}	t_info;

int		ft_strlen(char *str);
int		ft_atoi(char *str, int *integer);
int		ft_error(char *err_message);
double	get_ms_time();
int		*is_valid_arg(int argc, char **argv);
t_info	*init_info(int *philo_arg);

#endif