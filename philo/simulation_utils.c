/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/04 15:50:49 by skorbai          ###   ########.fr       */
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

void	ft_sleep(useconds_t duration, t_philo *philo)
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
	if (philo->need_to_die == 1)
	{
		wait_and_die(philo);
		return ;
	}
	ft_sleep(eat_time, philo);
	return ;
}

int	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;

	sleep_time = philo->time_to_sleep;
	check_for_dying(philo, 2);
	print_status(philo, "is sleeping");
	if (philo->need_to_die == 1)
	{
		wait_and_die(philo);
		return (1);
	}
	ft_sleep(sleep_time, philo);
	print_status(philo, "is thinking");
	return (0);
}

void	check_for_dying(t_philo *philo, int mode)
{
	useconds_t	time_elapsed;
	useconds_t	time_since_last_meal;
	useconds_t	logtime_to_finish_at;

	time_elapsed = get_elapsed_time(philo);
	time_since_last_meal = time_elapsed - philo->last_meal;
	logtime_to_finish_at = time_since_last_meal + philo->time_to_eat;
	if (mode == 2)
		logtime_to_finish_at = logtime_to_finish_at + philo->time_to_sleep;
	if (logtime_to_finish_at > (useconds_t)philo->time_to_die)
		philo->need_to_die = 1;
	else if (logtime_to_finish_at == (useconds_t)philo->time_to_die)
		philo->need_to_die = -1;
	else
		philo->need_to_die = 0;
}

/*
Notes:

last meal - at 30 ms elapsed

Current time: 70 ms elapsed

time to die: 80

time to eat: 30

time to sleep: 60

can we survive till we can eat again?

time since last meal: current time - last meal = 40

if we started eating now we'd be done in: 40 + 30 = 70 ms from now - eat would be finished, but we'd die while sleeping

*/