/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:29:54 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/02 11:02:59 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;

	if (argc != 5 || argc != 6)
	{
		printf("Error: number osf arguments must be 4 or 5\n");
		return (1);
	}
	params = init_params(argc, argv);
	if (params == NULL)
		return (1);
	printf("Parameters are:\n");
	printf("Number of philos: %d\n");
	printf("Time to die: %d\n");
	printf("Time to eat: %d\n");
	printf("Time to sleep: %d\n");
	printf("Eat threshold: %d\n");
}
