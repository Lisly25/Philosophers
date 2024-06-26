/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:09 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/11 10:22:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	get_elapsed_time(t_philo *philo)
{
	struct timeval	current_time;
	useconds_t		elapsed_usec;
	useconds_t		elapsed_sec;
	useconds_t		elapsed_milisec;

	gettimeofday(&current_time, NULL);
	elapsed_sec = (current_time.tv_sec - philo->start_sec) * 1000;
	if (elapsed_sec == 0)
		elapsed_usec = (current_time.tv_usec - philo->start_usec) / 1000;
	else
	{
		elapsed_usec = (1000 - (philo->start_usec / 1000)) + \
		(current_time.tv_usec / 1000);
		elapsed_sec -= 1000;
	}
	elapsed_milisec = elapsed_sec + elapsed_usec;
	return (elapsed_milisec);
}

void	print_status(t_philo *philo, char *message)
{
	useconds_t	time_elapsed;

	if (pthread_mutex_lock(philo->print_flag) != 0)
	{
		ft_putendl_fd("Error: pthread_mutex_lock", 2);
		set_death_flag(philo);
		return ;
	}
	if (check_kill_flag(philo) == 1 || check_if_opt_done(philo) == 1)
	{
		pthread_mutex_unlock(philo->print_flag);
		return ;
	}
	time_elapsed = get_elapsed_time(philo);
	printf("%u ms %d %s\n", time_elapsed, philo->nro + 1, message);
	pthread_mutex_unlock(philo->print_flag);
}

void	print_death_status(t_philo *philo, char *message)
{
	useconds_t	time_elapsed;

	if (pthread_mutex_lock(philo->print_flag) != 0)
	{
		ft_putendl_fd("Error: pthread_mutex_lock", 2);
		set_death_flag(philo);
		return ;
	}
	time_elapsed = get_elapsed_time(philo);
	printf("%u ms %d %s\n", time_elapsed, philo->nro + 1, message);
	pthread_mutex_unlock(philo->print_flag);
}
