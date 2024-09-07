/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:27:44 by mizem             #+#    #+#             */
/*   Updated: 2024/09/07 23:49:51 by mizem            ###   ########.fr       */
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
	size_t			last_meal;
	t_program		*program;
}					t_philos;

typedef struct s_program
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				food;
	size_t			start_time;
	int				is_dead;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	pthread_mutex_t dead_lock;
	t_philos		*philos;
}					t_program;

void *routine(void *philo);
size_t	get_current_time(void);

#endif