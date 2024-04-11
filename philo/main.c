/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:29:54 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/11 10:20:04 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;
	t_philo		**philos;

	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Error: number of arguments must be 4 or 5", 2);
		return (1);
	}
	if (argc == 6 && argv[5][0] == '0')
		return (0);
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
