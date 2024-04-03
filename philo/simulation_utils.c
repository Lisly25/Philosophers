/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 14:52:20 by skorbai          ###   ########.fr       */
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
			return ;
		else
			usleep(1);
	}
	else
	{
		if (philo->nro == 0)
			usleep(2);
		else if (philo->nro % 2 == 0)
			return ;
		else
			usleep(1);
	}
}

void	go_to_eat(t_philo *philo)
{
	useconds_t	eat_time;
	useconds_t	i;

	eat_time = philo->time_to_eat * 1000;
	i = 0;
	print_status(philo, "is eating");
	while (i != eat_time)
	{
		usleep(500);
		i = i + 500;
	}
}

void	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;
	useconds_t	i;

	sleep_time = philo->time_to_sleep * 1000;
	i = 0;
	print_status(philo, "is sleeping");
	while (i != sleep_time)
	{
		usleep(500);
		i = i + 500;
	}
}
