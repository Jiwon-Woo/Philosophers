#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

# define NUM_OF_PHILO 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUM_OF_EACH_MUST_EAT 4

# define FALSE 0
# define TRUE 1

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo {
	pid_t	id;
	int		idx;
	int		count_eat;
	double	last_eat;
	double	start_time;
	t_info	*info;
	int		fork;
	// sem_t	*rfork;
	// sem_t	*lfork;
}	t_philo;

typedef struct s_info {
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_each_must_eat;
	sem_t		*forks;
	t_philo		*philo;
	pthread_t	monitor;
	int			num_of_finish;
	int			someone_die;
	sem_t		*print;
	sem_t		*finish;
	sem_t		*die;
}	t_info;

int		ft_atoi(char *str, int *integer);
int		ft_strlen(char *str);
void	ft_print_status(double time, t_philo *philo, char *status);
void	ft_usleep(double time);
double	get_ms_time(void);
t_info	*free_info(t_info *info);
int		free_mutex(t_info *info);
int		ft_exit(t_info *info, char *error, int exit);
t_info	*init_info_philo(int argc, char **argv);
int		get_num_of_finish(t_info *info);
int		get_someone_die(t_info *info);
double	get_philo_last_eat(t_info *info, int i);
int		create_philo(t_info *info);
int		create_monitor(t_info *info);

#endif