/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:17:39 by jwoo              #+#    #+#             */
/*   Updated: 2021/09/26 14:19:05 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_num_of_finish(t_info *info)
{
	pthread_mutex_lock(&(info->finish));
	pthread_mutex_unlock(&(info->finish));
	return (info->num_of_finish);
}

int	get_someone_die(t_info *info)
{
	pthread_mutex_lock(&(info->die));
	pthread_mutex_unlock(&(info->die));
	return (info->someone_die);
}
