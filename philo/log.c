/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:09 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 16:32:33 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	get_elapsed_time(t_philo *philo)//misunderstood how gettimeofday works, need to rewrite this and all other time-related functions!
{
	struct timeval	current_time;
	useconds_t		time_elapsed;

	gettimeofday(&current_time, NULL);
	time_elapsed = (current_time.tv_usec / 1000) - (philo->start / 1000);
	return (time_elapsed);
}

void	print_status(t_philo *philo, char *message)
{
	useconds_t	time_elapsed;

	time_elapsed = get_elapsed_time(philo);
	printf("%ums: %d %s\n", time_elapsed, philo->nro + 1, message);
}
