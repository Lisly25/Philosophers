/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:30:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/04/04 15:25:23 by skorbai          ###   ########.fr       */
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
	int				need_to_die;
	useconds_t		start_usec;
	time_t			start_sec;
	useconds_t		last_meal;
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
useconds_t	get_elapsed_time(t_philo *philo);
void		print_status(t_philo *philo, char *message);

//simulation_utils.c
void		set_start_pattern(t_philo *philo);
int			go_to_sleep(t_philo *philo);
void		go_to_eat(t_philo *philo);
void		check_for_dying(t_philo *philo, int mode);
void		ft_sleep(useconds_t duration, t_philo *philo);

//simulation_utils_2.c
void		wait_and_die(t_philo *philo);
void		try_to_get_fork_and_die(t_philo *philo);
void		wait_for_fork(t_philo *philo);

#endif