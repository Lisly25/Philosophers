/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:30:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/03 11:41:08 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

# define LONG_MAX 9223372036854775807

typedef struct s_params
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_threshold;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	own_fork;
	pthread_mutex_t	*other_fork;
	int				nro;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_threshold;
	suseconds_t		start;
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
void		destroy_mutexes(t_philo **philos, int i);
int			clean_strcts(t_philo **philos, t_params *params, char *str, int i);

//init_philos.c
t_philo		**init_philos(t_params *params);

//simulate.c
void		simulate(t_params *params, t_philo **philos);

//log.c
void		print_time(t_philo *philo);

//simulation_utils.c
void		get_start_time(t_philo *philo);
void		set_start_pattern(t_philo *philo);

#endif