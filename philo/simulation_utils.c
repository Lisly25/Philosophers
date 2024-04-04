/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/04 12:09:04 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	ft_sleep(useconds_t duration, t_philo *philo)
{
	useconds_t	elapsed_time;
	useconds_t	elapsed_time_goal;

	elapsed_time = get_elapsed_time(philo);
	elapsed_time_goal = (elapsed_time + duration);
	while (elapsed_time < elapsed_time_goal)
	{
		usleep(500);
		elapsed_time = get_elapsed_time(philo);
	}
}

void	go_to_eat(t_philo *philo)
{
	useconds_t	eat_time;

	eat_time = philo->time_to_eat;
	print_status(philo, "is eating");
	ft_sleep(eat_time, philo);
}

void	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;

	sleep_time = philo->time_to_sleep;
	print_status(philo, "is sleeping");
	ft_sleep(sleep_time, philo);
}
