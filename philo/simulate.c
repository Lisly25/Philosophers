/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:52 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/10 11:06:22 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_philo *philo)
{
	usleep(1);
	if (philo->philo_count == 1)
	{
		print_status(philo, "has taken a fork");
		wait_and_die(philo);
		return ;
	}
	set_start_pattern(philo);
	while (1)
	{
		check_for_dying(philo, 1);
		if (philo->need_to_die == 1)
		{
			try_to_get_fork_and_die(philo);
			return ;
		}
		else if (philo->need_to_die == 2)
			return (wait_and_die(philo));
		else
			if (wait_for_fork(philo) != 0)
				return ;
		if (go_to_sleep(philo) != 0)
			return ;
	}
}

static int	init_fork_mutexes(t_philo **philos, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		if (pthread_mutex_init(&philos[i]->own_fork, NULL) != 0)
		{
			destroy_fork_mutexes(philos, i);
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

	i = 0;
	gettimeofday(&start, NULL);
	while (i < params->philo_count)
	{
		philos[i]->start_sec = start.tv_sec;
		philos[i]->start_usec = start.tv_usec;
		philos[i]->death_flag = &(params->death_monitor);
		philos[i]->kill_signal = &(philos[0]->kill_all);
		philos[i]->print_flag = &(params->print_monitor);
		philos[i]->eat_count_mutex_ptr = &(params->eat_count_monitor);
		philos[i]->eat_count_ptr = &(philos[0]->eat_count_all);
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
	if (init_fork_mutexes(philos, params) == -1)
		return ;
	if (init_monitor_mutexes(params, philos) == -1)
		return ;
	if (init_threads(params, philos) == -1)
		return ;
	join_threads(params, philos);
}
