/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:56:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/11 10:21:38 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_death_flag(t_philo *philo)
{
	if (pthread_mutex_lock(philo->death_flag) != 0)
	{
		ft_putendl_fd("Mutex_lock_failed", 2);
		return (-1);
	}
	*(philo->kill_signal) = 1;
	pthread_mutex_unlock(philo->death_flag);
	return (0);
}

void	unlock_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->own_fork);
	pthread_mutex_unlock(philo->other_fork);
}

int	init_monitor_mutexes(t_params *params, t_philo **philos)
{
	if (pthread_mutex_init(&params->death_monitor, NULL) != 0)
	{
		destroy_forks_and_free(philos, params);
		return (-1);
	}
	if (pthread_mutex_init(&params->print_monitor, NULL) != 0)
	{
		pthread_mutex_destroy(&params->death_monitor);
		destroy_forks_and_free(philos, params);
		return (-1);
	}
	if (pthread_mutex_init(&params->eat_count_monitor, NULL) != 0)
	{
		pthread_mutex_destroy(&params->death_monitor);
		pthread_mutex_destroy(&params->print_monitor);
		destroy_forks_and_free(philos, params);
		return (-1);
	}
	return (0);
}

int	increment_eat_count(t_philo *philo)
{
	philo->own_eat_count = philo->own_eat_count + 1;
	if (philo->own_eat_count != philo->eat_threshold)
		return (0);
	if (pthread_mutex_lock(philo->eat_count_mutex_ptr) != 0)
	{
		ft_putendl_fd("Mutex_lock_failed", 2);
		set_death_flag(philo);
		return (-1);
	}
	*(philo->eat_count_ptr) = *(philo->eat_count_ptr) + 1;
	pthread_mutex_unlock(philo->eat_count_mutex_ptr);
	return (0);
}

int	check_if_opt_done(t_philo *philo)
{
	int	result;

	if (pthread_mutex_lock(philo->eat_count_mutex_ptr) != 0)
	{
		ft_putendl_fd("Mutex_lock_failed", 2);
		set_death_flag(philo);
		return (-1);
	}
	if (*(philo->eat_count_ptr) == philo->philo_count)
		result = 1;
	else
		result = 0;
	pthread_mutex_unlock(philo->eat_count_mutex_ptr);
	return (result);
}
