/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:56:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/08 12:53:34 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_death_flag(t_philo *philo)
{
	if (pthread_mutex_lock(philo->death_flag) != 0)
	{
		printf("Mutex_lock_failed\n");
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

int	init_monitor_mutexes(t_params *params, t_philo **philos)//the fork-mutexes should also be destroyed on error!
{
	if (pthread_mutex_init(&params->death_monitor, NULL) != 0)
	{
		printf("Error: pthread_mutex_init\n");
		free_philos(philos, params);
		free(params);
		return (-1);
	}
	if (pthread_mutex_init(&params->print_monitor, NULL) != 0)
	{
		printf("Error: pthread_mutex_init\n");
		free_philos(philos, params);
		free(params);
		pthread_mutex_destroy(&params->death_monitor);
		return (-1);
	}
	if (pthread_mutex_init(&params->eat_count_monitor, NULL) != 0)
	{
		printf("Error: pthread_mutex_init\n");
		free_philos(philos, params);
		free(params);
		pthread_mutex_destroy(&params->death_monitor);
		pthread_mutex_destroy(&params->print_monitor);
		return (-1);
	}
	return (0);
}

int	increment_eat_count(t_philo *philo)
{
	
}