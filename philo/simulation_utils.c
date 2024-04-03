/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 15:41:29 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	get_start_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_usec);
}

void	set_start_pattern(t_philo *philo)
{
	if (philo->philo_count % 2 == 0)
	{
		if (philo->nro % 2 == 0)
			return ;
		else
			usleep(100);
	}
	else
	{
		if (philo->nro == 0)
			usleep(200);
		else if (philo->nro % 2 == 0)
			return ;
		else
			usleep(100);
	}
}

void	go_to_eat(t_philo *philo)
{
	useconds_t	eat_time;

	eat_time = philo->time_to_eat * 1000;
	print_status(philo, "is eating");
	usleep(eat_time);
}

void	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;

	sleep_time = philo->time_to_sleep * 1000;
	print_status(philo, "is sleeping");
	usleep(sleep_time);
}
