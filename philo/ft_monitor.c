/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:17:33 by jwoo              #+#    #+#             */
/*   Updated: 2021/09/22 19:17:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_starving(t_info *info, int i)
{
	double	base;

	base = get_philo_last_eat(info, i);
	if (base == 0)
		base = info->philo[i].start_time;
	if (get_ms_time() - base > info->time_to_die)
	{
		ft_usleep(2);
		pthread_mutex_lock(&(info->die));
		info->someone_die = TRUE;
		pthread_mutex_unlock(&(info->die));
		return (1);
	}
	return (0);
}

void	*die_or_finish(t_info *info, int i)
{
	pthread_mutex_lock(&(info->print));
	if (get_num_of_finish(info) == info->num_of_philo)
		printf("\x1b[32m%6dms   SUCCESS! Everyone finished their meal.\x1b[0m\n", \
		(int)(get_ms_time() - info->philo[i % info->num_of_philo].start_time));
	else if (get_someone_die(info))
		printf("\x1b[31m%6dms   Philosopher %-3d  died\x1b[0m\n", \
		(int)(get_ms_time() - info->philo[i].start_time), info->philo[i].idx);
	pthread_mutex_unlock(&(info->print));
	return ((void *)0);
}

void	*monitor_routine(void *v_info)
{
	t_info	*info;
	int		i;

	info = (t_info *)v_info;
	while (!get_someone_die(info) && \
		get_num_of_finish(info) < info->num_of_philo)
	{
		i = -1;
		while (++i < info->num_of_philo && \
			get_num_of_finish(info) < info->num_of_philo)
		{
			if (philo_starving(info, i))
				break ;
			ft_usleep(0.01);
		}
	}
	return (die_or_finish(info, i));
}

int	create_monitor(t_info *info)
{
	ft_usleep(0.1);
	if (pthread_create(&(info->monitor), NULL, monitor_routine, (void *)(info)))
		return (-1);
	pthread_join(info->monitor, NULL);
	return (1);
}
