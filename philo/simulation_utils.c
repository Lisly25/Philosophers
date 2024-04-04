/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/04 12:53:17 by skorbai          ###   ########.fr       */
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
	philo->last_meal = get_elapsed_time(philo);
	ft_sleep(eat_time, philo);
}

void	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;

	sleep_time = philo->time_to_sleep;
	print_status(philo, "is sleeping");
	ft_sleep(sleep_time, philo);
}

int	die_if_needed(t_philo *philo)//returns 1 if philo would die before finishing to eat - BUT it should still start eating, it should just not finish!
{
	useconds_t	time_elapsed;
	useconds_t	time_since_last_meal;
	useconds_t	max_lifetime;

	time_elapsed = get_elapsed_time(philo);
	time_since_last_meal = time_elapsed - philo->last_meal;
	max_lifetime = philo->time_to_eat + time_since_last_meal;
	if (max_lifetime < philo->time_to_die)
		return (1);
	return (0);
}//we probably also want to check if it's time to die during the sleeping time!

/*
Notes:

last meal - at 30 ms elapsed

Current time: 60 ms elapsed

time to die: 200

time to eat: 60

time to sleep: 60

can we survive till we can eat again?

time since last meal: current time - last meal = 30

if we started eating now we'd be done in: 30 + 30 = 60 ms from now - well under 200

*/