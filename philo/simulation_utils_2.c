/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:01 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/05 10:25:49 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_and_die(t_philo *philo)
{
	useconds_t	time_remaining;
	useconds_t	time_elapsed;

	time_elapsed = get_elapsed_time(philo);
	if (philo->last_meal != 0)
		time_remaining = philo->time_to_die - (time_elapsed - philo->last_meal);
	else
		time_remaining = philo->time_to_die - time_elapsed;
	ft_sleep(time_remaining, philo);
	print_status(philo, "is dead");
}

int	check_if_philo_starts_in_2nd_wave(t_philo *philo)
{
	if (philo->philo_count % 2 == 0)
	{
		if (philo->nro % 2 == 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (philo->nro == 0)
			return (1);
		else if (philo->nro % 2 == 0)
			return (0);
		else
			return (1);
	}
}

void	try_to_get_fork_and_die(t_philo *philo)
{
	if (philo->time_to_die >= philo->time_to_eat)
	{
		if (check_if_philo_starts_in_2nd_wave(philo) == 1)
			return (wait_and_die(philo));
	}
	//else if (philo->time_to_die == philo->time_to_eat)
	//{
	//	if (check_if_philo_starts_in_2nd_wave(philo) == 1)
	//		return (wait_and_die(philo));
	//	else
	//		(wait_for_fork(philo));
	//}
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
