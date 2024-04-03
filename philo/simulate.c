/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:52 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 10:07:11 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_params *params)
{
	struct timeval	current_time;
	suseconds_t		time_elapsed;

	gettimeofday(&current_time, NULL);
	time_elapsed = (current_time.tv_usec - params->start) / 1000;
	printf("Time since simulation start in microseconds: %d\n", time_elapsed);
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
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		if (pthread_create(&philos[i]->thread, NULL, (void *)(*philo_cycle), \
		(void *)params) != 0)
		{
			destroy_mutexes(philos, i);
			free_philos(philos, params);
			free(params);
			return (-1);
		}
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
	struct timeval	start;

	if (init_locks(philos, params) == -1)
		return ;
	if (gettimeofday(&start, NULL) != 0)
	{
		free_philos(philos, params);
		free(params);
		return ;
	}
	params->start = start.tv_usec;
	if (init_threads(params, philos) == -1)
		return ;
	join_threads(params, philos);
}
