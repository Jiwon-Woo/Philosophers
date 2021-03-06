/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:17:25 by jwoo              #+#    #+#             */
/*   Updated: 2021/09/26 14:13:06 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == 0)
		return (-1);
	while (str[len])
		len++;
	return (len);
}

void	ft_print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&(philo->info->print));
	if (get_someone_die(philo->info))
	{
		pthread_mutex_unlock(&(philo->info->print));
		return ;
	}
	if (ft_strncmp(status, "is eating", ft_strlen("is eating") + 1) == 0)
	{
		philo->last_eat = get_ms_time();
		printf("%6dms   Philosopher %-3d  %s\n", \
			(int)(philo->last_eat - philo->start_time), philo->idx, status);
	}
	else
	{
		printf("%6dms   Philosopher %-3d  %s\n", \
			(int)(get_ms_time() - philo->start_time), philo->idx, status);
	}
	pthread_mutex_unlock(&(philo->info->print));
}

void	ft_usleep(double time)
{
	double	start;

	start = get_ms_time();
	while (time >= get_ms_time() - start)
	{
		usleep(10);
	}
}

double	get_ms_time(void)
{
	struct timeval	time;
	double			time_ms;

	gettimeofday(&time, 0);
	time_ms = time.tv_sec * 1000 + ((double)time.tv_usec / 1000);
	return (time_ms);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		len;

	if (n == 0)
		return (0);
	len = 0;
	while (len + 1 < n && s1[len] && s2[len])
	{
		if (s1[len] == s2[len])
			len++;
		else
			break ;
	}
	return (s1[len] - s2[len]);
}
