/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:27:44 by mizem             #+#    #+#             */
/*   Updated: 2024/09/08 22:49:46 by mizem            ###   ########.fr       */
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
	size_t				num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				food;
	size_t				start_time;
	size_t				is_dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t 	print;
	pthread_mutex_t 	dead_lock;
	t_philos			*philos;
}			t_program;

void *routine(void *philo);
size_t	get_current_time(void);
void is_print(t_philos *philo, char *str);

#endif