/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:09 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 15:26:23 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time(t_philo *philo)
{
	struct timeval	current_time;
	useconds_t		time_elapsed;

	gettimeofday(&current_time, NULL);
	time_elapsed = (current_time.tv_usec - philo->start) / 1000;
	printf("%ums: ", time_elapsed);
}

void	print_status(t_philo *philo, char *message)
{
	print_time(philo);
	printf("%d %s\n", philo->nro + 1, message);
}
