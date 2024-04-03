/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:29:54 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 15:02:51 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;
	t_philo		**philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error: number of arguments must be 4 or 5\n");
		return (1);
	}
	params = init_params(argc, argv);
	if (params == NULL)
		return (1);
	philos = init_philos(params);
	if (philos == NULL)
		return (1);
	simulate(params, philos);
	free_philos(philos, params);
	free(params);
}
