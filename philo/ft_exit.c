/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:17:29 by jwoo              #+#    #+#             */
/*   Updated: 2021/09/28 09:48:39 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_mutex(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_unlock(&(info->forks[i]));
	if (&(info->die))
		pthread_mutex_unlock(&(info->die));
	if (&(info->print))
		pthread_mutex_unlock(&(info->print));
	if (&(info->finish))
		pthread_mutex_unlock(&(info->finish));
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	if (&(info->die))
		pthread_mutex_destroy(&(info->die));
	if (&(info->print))
		pthread_mutex_destroy(&(info->print));
	if (&(info->finish))
		pthread_mutex_destroy(&(info->finish));
	return (0);
}

t_info	*free_info(t_info *info)
{
	if (info->philo)
		free(info->philo);
	if (info->forks)
		free(info->forks);
	info->philo = 0;
	info->forks = 0;
	free(info);
	return (0);
}

int	ft_exit(t_info *info, char *error, int exit)
{
	if (error)
		write(1, error, ft_strlen(error));
	if (info == 0)
		return (exit);
	free_mutex(info);
	free_info(info);
	return (exit);
}
