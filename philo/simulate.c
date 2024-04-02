/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:52 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/02 14:59:48 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_params *params)
{
	struct timeval	*current_time;
	suseconds_t		time_elapsed;

	gettimeofday(current_time, NULL);
	time_elapsed = (current_time->tv_usec - params->start.tv_usec) / 1000;
	printf("Time since simulation start in microseconds: %d\n", time_elapsed);
}

static int	init_locks(t_philo **philos, t_params *params)
{
	int	i;

	i = 0;
	while (i < params)
	{
		if (pthread_mutex_init(philos[i]->left_fork, NULL) != 0)
		{
			free(params);
			free_philos(philos);
			return (-1);
		}
		if (pthread_mutex_init(philos[i]->right_fork, NULL) != 0)
		{
			free(params);
			free_philos(philos);
			return (-1);
		}
		i++;
	}
}

static int	init_threads(t_params *params, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		if (pthread_create(philos[i]->thread, NULL, (*philo_cycle), \
		(void *)params) != 0)
		{
			free(params);
			destroy_threads(philos, i);
			free_philos(philos);
			return (-1);
		}
	}
}

void	simulate(t_params *params, t_philo **philos)
{
	if (init_locks(philos, params) == -1)
		return ;
	if (gettimeofday(&params->start, NULL) != 0)
	{
		free(params);
		free_philos(philos);
		return ;
	}
	if (init_threads(params, philos) == -1)
		return ;
}
