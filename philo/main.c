/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:17:22 by jwoo              #+#    #+#             */
/*   Updated: 2021/09/22 19:17:23 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_info(argc, argv);
	if (info == 0)
		return (ft_exit(NULL, "Error\n", 1));
	if (create_philo(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	if (create_monitor(info) < 0)
		return (ft_exit(info, "Error\n", 1));
	return (ft_exit(info, NULL, 0));
}
