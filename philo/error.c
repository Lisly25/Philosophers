/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:10:57 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/08 12:44:50 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_strcts(t_philo **philos, t_params *params, char *error, int i)
{
	printf("%s", error);
	destroy_mutexes(philos, i, params);
	free_philos(philos, params);
	free(params);
	return (-1);
}

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

void	destroy_mutexes(t_philo **philos, int i, t_params *params)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&philos[j]->own_fork);
		j++;
	}
	pthread_mutex_destroy(&params->death_monitor);
	pthread_mutex_destroy(&params->print_monitor);
	pthread_mutex_destroy(&params->eat_count_monitor);
}

//I'll have this use printf normally for now, but I might want to utilize the print mutex
int	print_error_and_return_1(char *msg, t_philo *philo, int lock_nr)
{
	printf("Thread %d: %s\n", philo->nro + 1, msg);
	set_death_flag(philo);
	if (lock_nr == 2)
		pthread_mutex_unlock(&philo->own_fork);
	return (1);
}

void	print_error(char *msg, t_philo *philo, int lock_nr)
{
	printf("Thread %d: %s\n", philo->nro + 1, msg);
	set_death_flag(philo);
	if (lock_nr == 2)
		pthread_mutex_unlock(&philo->own_fork);
}
