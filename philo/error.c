/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:10:57 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 09:46:41 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo **philos, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	destroy_mutexes(t_philo **philos, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&philos[j]->own_fork);
		j++;
	}
}
