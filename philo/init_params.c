/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:38:15 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/09 15:12:07 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	insert_param_to_struct(int arg, int i, t_params *params)
{
	if (i == 1)
		params->philo_count = arg;
	if (i == 2)
		params->time_to_die = arg;
	if (i == 3)
		params->time_to_eat = arg;
	if (i == 4)
		params->time_to_sleep = arg;
	if (i == 5)
		params->eat_threshold = arg;
}

static int	check_if_arg_is_valid(int arg, int i, t_params *params)
{
	if (arg < 0)
	{
		printf("Error: arguments can't be negative numbers\n");
		return (-1);
	}
	if (arg == 0 && i != 5)
	{
		printf("Error: only the optional argument can be 0\n");
		return (-1);
	}
	insert_param_to_struct(arg, i, params);
	return (0);
}

static int	init_param(int i, char *arg, t_params *params)
{
	int		arg_num;
	char	*arg_str;

	arg_num = ft_atoi(arg);
	arg_str = ft_itoa(arg_num);
	if (arg_str == NULL)
	{
		printf("Error: malloc failure\n");
		return (-1);
	}
	if (ft_strlen(arg) != ft_strlen(arg_str))
	{
		free(arg_str);
		printf("Error: %s: is not an integer\n", arg);
		return (-1);
	}
	if (ft_strncmp(arg, arg_str, ft_strlen(arg)) != 0)
	{
		free(arg_str);
		printf("Error: %s: is not an integer\n", arg);
		return (-1);
	}
	free(arg_str);
	return (check_if_arg_is_valid(arg_num, i, params));
}

t_params	*init_params(int argc, char **argv)
{
	t_params	*params;
	int			i;

	params = malloc(sizeof(t_params));
	if (params == NULL)
	{
		printf("Error: malloc failure\n");
		return (NULL);
	}
	i = 1;
	while (i < argc)
	{
		if (init_param(i, argv[i], params) == -1)
		{
			free(params);
			return (NULL);
		}
		i++;
	}
	if (argc == 5)
		params->eat_threshold = -1;
	return (params);
}
