/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:59:44 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/05 10:52:51 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	**copy_params_to_philos(t_params *params, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < params->philo_count)
	{
		philos[i]->nro = i;
		philos[i]->eat_threshold = params->eat_threshold;
		philos[i]->philo_count = params->philo_count;
		philos[i]->time_to_die = params->time_to_die;
		philos[i]->time_to_eat = params->time_to_eat;
		philos[i]->time_to_sleep = params->time_to_sleep;
		philos[i]->last_meal = 0;
		philos[i]->kill_signal = 0;
		i++;
	}
	return (philos);
}

t_philo	**init_philos(t_params *params)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo *) * (params->philo_count + 1));
	if (philos == NULL)
	{
		printf("Error: malloc failure\n");
		free(params);
		return (NULL);
	}
	while (i < params->philo_count)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (philos[i] == NULL)
		{
			printf("Error: malloc failure\n");
			free_philos(philos, params);
			free(params);
			return (NULL);
		}
		i++;
	}
	philos[i] = NULL;
	return (copy_params_to_philos(params, philos));
}
