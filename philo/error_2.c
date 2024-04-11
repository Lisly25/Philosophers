/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:02:16 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/11 10:38:12 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork_mutexes(t_philo **philos, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&philos[j]->own_fork);
		j++;
	}
}

void	destroy_forks_and_free(t_philo **philos, t_params *params)
{
	destroy_fork_mutexes(philos, params->philo_count);
	free_philos(philos, params);
	free(params);
}
