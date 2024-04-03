/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 11:38:01 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_start_time(t_philo *philo)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) != 0)
	{
		free(philo);
		return ;
	}
	philo->start = start.tv_usec;
}

void	set_start_pattern(t_philo *philo)
{
	if (philo->philo_count % 2 == 0)
	{
		if (philo->nro % 2 == 0)
			usleep(1);
		else
			return ;
	}
	else
	{
		if (philo->nro == 0)
			usleep(2);
		else if (philo->nro % 2 == 0)
			usleep(1);
		else
			return ;
	}
}
