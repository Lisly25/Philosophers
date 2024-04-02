/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:30:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/02 15:48:49 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define LONG_MAX 9223372036854775807

typedef struct s_params
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_threshold;
	suseconds_t		start;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
}	t_philo;

//init_params.c
t_params	*init_params(int argc, char **argv);

//utils.c
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_itoa.c
char		*ft_itoa(int n);

//error.c
void		free_philos(t_philo **philos, t_params *params);

//init_philos.c
t_philo		**init_philos(t_params *params);

//simulate.c
void		simulate(t_params *params, t_philo **philos);

#endif