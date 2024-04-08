/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/08 10:36:55 by skorbai          ###   ########.fr       */
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

void	ft_sleep(useconds_t duration, t_philo *philo)//will need to check how much the simulation would be slowed by checking for the death flag every loop
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

int	go_to_eat(t_philo *philo)
{
	useconds_t	eat_time;

	eat_time = philo->time_to_eat;
	if (check_kill_flag(philo) == 1)
	{
		pthread_mutex_unlock(&philo->own_fork);
		pthread_mutex_unlock(philo->other_fork);
		return (1);
	}
	print_status(philo, "is eating");
	philo->last_meal = get_elapsed_time(philo);
	if (philo->need_to_die == 1)
	{
		wait_and_die(philo);
		return (1);
	}
	ft_sleep(eat_time, philo);
	return (0);
}

int	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;

	sleep_time = philo->time_to_sleep;
	if (check_kill_flag(philo) == 1)
		return (1);
	check_for_dying(philo, 2);
	if (check_kill_flag(philo) == 1)
		return (1);
	print_status(philo, "is sleeping");
	if (philo->need_to_die == 1)
	{
		wait_and_die(philo);
		return (1);
	}
	ft_sleep(sleep_time, philo);
	if (check_kill_flag(philo) == 1)
		return (1);
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
		logtime_to_finish_at = time_since_last_meal + philo->time_to_sleep;
	if (logtime_to_finish_at > (useconds_t)philo->time_to_die)
		philo->need_to_die = 1;
	else if (logtime_to_finish_at == (useconds_t)philo->time_to_die)
		philo->need_to_die = -1;
	else
		philo->need_to_die = 0;
}
