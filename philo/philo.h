/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:17:14 by jwoo              #+#    #+#             */
/*   Updated: 2021/09/28 09:50:02 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define FALSE 0
# define TRUE 1

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo {
	int				idx;
	int				count_eat;
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
	pthread_t		monitor;
	int				num_of_finish;
	int				someone_die;
	pthread_mutex_t	print;
	pthread_mutex_t	finish;
	pthread_mutex_t	die;
}	t_info;

int		ft_atoi(char *str, int *integer);
int		ft_strlen(char *str);
void	ft_print_status(t_philo *philo, char *status);
void	ft_usleep(double time);
double	get_ms_time(void);
int		ft_strncmp(char *s1, char *s2, int n);
t_info	*free_info(t_info *info);
int		free_mutex(t_info *info);
int		ft_exit(t_info *info, char *error, int exit);
t_info	*init_info(int argc, char **argv);
int		get_num_of_finish(t_info *info);
int		get_someone_die(t_info *info);
int		create_philo(t_info *info);
int		create_monitor(t_info *info);

#endif