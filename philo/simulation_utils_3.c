/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:56:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/05 12:30:00 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_death_flag(t_philo *philo)
{
	if (pthread_mutex_lock(philo->death_flag) != 0)
	{
		printf("Mutex_lock_failed\n");
		return (-1);
	}
	philo->kill_signal = 1;
	pthread_mutex_unlock(philo->death_flag);
	return (0);
}
