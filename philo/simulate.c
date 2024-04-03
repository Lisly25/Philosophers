/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:52 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 15:25:32 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_philo *philo)
{
	if (philo->philo_count == 1)
	{
		printf("For now, just print this and stop\n");
		return ;
	}
	set_start_pattern(philo);
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
	go_to_sleep(philo);
	return ;
}

static int	init_locks(t_philo **philos, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		if (pthread_mutex_init(&philos[i]->own_fork, NULL) != 0)
		{
			free_philos(philos, params);
			free(params);
			return (-1);
		}
		i++;
	}
	if (params->philo_count > 1)
		philos[0]->other_fork = &(philos[params->philo_count - 1]->own_fork);
	else
		philos[0]->other_fork = NULL;
	i = params->philo_count - 1;
	while (i > 0)
	{
		philos[i]->other_fork = &(philos[i - 1]->own_fork);
		i--;
	}
	return (0);
}

static int	init_threads(t_params *params, t_philo **philos)
{
	int			i;
	useconds_t	start;

	i = 0;
	start = get_start_time();
	while (i < params->philo_count)
	{
		philos[i]->start = start;
		if (pthread_create(&philos[i]->thread, NULL, (void *)(*philo_cycle), \
		(void *)philos[i]) != 0)
			return (clean_strcts(philos, params, "Error: pthread_create\n", i));
		i++;
	}
	return (0);
}

static void	join_threads(t_params *params, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
}

void	simulate(t_params *params, t_philo **philos)
{
	if (init_locks(philos, params) == -1)
		return ;
	if (init_threads(params, philos) == -1)
		return ;
	join_threads(params, philos);
}
