/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:27:44 by mizem             #+#    #+#             */
/*   Updated: 2024/09/13 22:33:28 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>

int	ft_atoi(char *str);
int	ft_strlen(char *s);

typedef struct s_program t_program;

typedef struct s_philos
{
	pthread_t		thread;
	int				id;
	int				l_fork;
	int				r_fork;
	int				meals;
	size_t			last_meal;
	t_program		*program;
}					t_philos;

typedef struct s_program
{
	int				num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int				food;
	size_t				start_time;
	size_t				is_dead;
	int					full;
	pthread_mutex_t		*forks;
	pthread_mutex_t 	print;
	pthread_mutex_t 	dead_lock;
	pthread_mutex_t		last_meal_mut;
	pthread_mutex_t		meals_mut;
	pthread_mutex_t		full_mut;
	t_philos			*philos;
}			t_program;

void *routine(void *philo);
size_t	get_current_time(void);
int  is_usleep(size_t milliseconds, t_program *prg);
void is_print(t_philos *philo, char *str);
int special_one(t_program *prg);
int give_nmeals(t_philos *philo);
void create_threads(t_program *prg, int philos);
void join_threads(t_program *prg, int philos);
int give_nmeals(t_philos *philo);
int mutex_flag(t_philos *philo);
void clear_all(t_program *prg);

#endif