/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:59:44 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/02 15:49:54 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (philos);
}
