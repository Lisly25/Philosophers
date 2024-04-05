/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:52 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/05 12:48:35 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_philo *philo)
{
	usleep(1);
	if (philo->philo_count == 1)
	{
		printf("For now, just print this and stop\n");
		return ;
	}
	set_start_pattern(philo);
	while (1)
	{
		check_for_dying(philo, 1);
		if (philo->need_to_die == 1 || (philo->need_to_die == -1 && \
		check_if_philo_starts_in_2nd_wave(philo) == 1))
		{
			try_to_get_fork_and_die(philo);
			return ;
		}
		else
			if (wait_for_fork(philo) != 0)
				return ;
		if (go_to_sleep(philo) != 0)
			return ;
	}
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
	int				i;
	struct timeval	start;
	pthread_mutex_t	death_flag;

	i = 0;
	if (pthread_mutex_init(&death_flag, NULL) != 0)
		return (clean_strcts(philos, params, "Error: pthread_mutex_init\n", i));
	gettimeofday(&start, NULL);//should I error check this?
	while (i < params->philo_count)
	{
		philos[i]->start_sec = start.tv_sec;
		philos[i]->start_usec = start.tv_usec;
		philos[i]->death_flag = &death_flag;
		if (pthread_create(&philos[i]->thread, NULL, (void *)(*philo_cycle), \
		(void *)philos[i]) != 0)
		{
			pthread_mutex_destroy(&death_flag);
			return (clean_strcts(philos, params, "Error: pthread_create\n", i));
		}
		i++;
	}
	pthread_mutex_destroy(&death_flag);
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
