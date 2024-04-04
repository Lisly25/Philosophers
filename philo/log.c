/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:09 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/04 10:52:41 by skorbai          ###   ########.fr       */
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
	//printf("Current time usec: %u\n", current_time.tv_usec);
	//printf("Start usec: %u\n", philo->start_usec);
	elapsed_sec = (current_time.tv_sec - philo->start_sec) * 1000;
	if (elapsed_sec == 0)
		elapsed_usec = (current_time.tv_usec - philo->start_usec) / 1000;
	else
	{
		elapsed_usec = (1000 - (philo->start_usec / 1000)) + (current_time.tv_usec / 1000);
		elapsed_sec -= 1000;
	}
	elapsed_milisec = elapsed_sec + elapsed_usec;
	printf("Elapsed sec: %u\n", elapsed_sec);
	printf("Elapsed usec: %u\n", elapsed_usec);
	return (elapsed_milisec);
}

void	print_status(t_philo *philo, char *message)
{
	useconds_t	time_elapsed;

	time_elapsed = get_elapsed_time(philo);
	printf("%ums: %d %s\n", time_elapsed, philo->nro + 1, message);
}

/*
pl:

start: 1 sec 999999 usec

current: 2 sec 1 usec

elapsed:

1000000 - 999999 usec + current usec

sec: -1 of difference

*/