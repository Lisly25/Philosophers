/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:01 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/04 15:50:58 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_and_die(t_philo *philo)
{
	useconds_t	time_remaining;
	useconds_t	time_elapsed;

	time_elapsed = get_elapsed_time(philo);
	time_remaining = philo->time_to_die - (time_elapsed - philo->last_meal);
	ft_sleep(time_remaining, philo);
	print_status(philo, "is dead");
}

void	try_to_get_fork_and_die(t_philo *philo)
{
	if (philo->need_to_die == -1)
		return (wait_and_die(philo));
	if (pthread_mutex_lock(&philo->own_fork) != 0)
	{
		printf("Mutex_lock_failed\n");
		return ;
	}
	print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->other_fork) != 0)
	{
		printf("Mutex_lock_failed\n");
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->other_fork);
	pthread_mutex_unlock(&philo->own_fork);
	go_to_eat(philo);
}

void	wait_for_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->own_fork) != 0)
	{
		printf("Mutex_lock_failed\n");
		return ;
	}
	print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->other_fork) != 0)
	{
		printf("Mutex_lock_failed\n");
		return ;
	}
	print_status(philo, "has taken a fork");
	go_to_eat(philo);
	pthread_mutex_unlock(philo->other_fork);
	pthread_mutex_unlock(&philo->own_fork);
}
