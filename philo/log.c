/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:09 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 11:05:56 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time(t_philo *philo)
{
	struct timeval	current_time;
	suseconds_t		time_elapsed;

	gettimeofday(&current_time, NULL);
	time_elapsed = (current_time.tv_usec - philo->start) / 1000;
	printf("%d ", time_elapsed);
}
