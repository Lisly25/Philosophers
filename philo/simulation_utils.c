/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/09 10:49:48 by skorbai          ###   ########.fr       */
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
	if (check_kill_flag(philo) == 1 || check_if_opt_done(philo) == 1)
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
		unlock_both_forks(philo);
		return (1);
	}
	ft_sleep(eat_time, philo);
	increment_eat_count(philo);
	unlock_both_forks(philo);
	if (check_if_opt_done(philo) == 1)
		return (1);
	return (0);
}

int	go_to_sleep(t_philo *philo)
{
	useconds_t	sleep_time;

	sleep_time = philo->time_to_sleep;
	if (check_kill_flag(philo) == 1 || check_if_opt_done(philo) == 1)
		return (1);
	print_status(philo, "is sleeping");
	check_for_dying(philo, 2);
	if (check_if_opt_done(philo) == 1)
		return (1);
	if (philo->need_to_die == 1)
	{
		wait_and_die(philo);
		return (1);
	}
	if (check_if_opt_done(philo) == 1)
		return (1);
	ft_sleep(sleep_time, philo);
	if (check_if_opt_done(philo) == 1)
		return (1);
	print_status(philo, "is thinking");
	return (0);
}

void	check_for_dying(t_philo *philo, int mode)
{
	useconds_t	time_since_last_meal_ms;
	useconds_t	min_time_to_next_eat;
	useconds_t	timestamp_current;

	if (mode == 1 && philo->time_to_eat > philo->time_to_die)
	{
		philo->need_to_die = 1;
		return ;
	}
	timestamp_current = get_elapsed_time(philo);
	time_since_last_meal_ms = timestamp_current - philo->last_meal;
	if (mode == 1)
		min_time_to_next_eat = time_since_last_meal_ms;
	else
		min_time_to_next_eat = time_since_last_meal_ms + philo->time_to_sleep;
	if (min_time_to_next_eat > (useconds_t)philo->time_to_die)
		philo->need_to_die = 1;
	else
		philo->need_to_die = 0;
}
