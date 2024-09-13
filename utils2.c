/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:24:06 by mizem             #+#    #+#             */
/*   Updated: 2024/09/13 22:24:37 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int  is_usleep(size_t milliseconds, t_program *prg)
{
	(void)prg;
	size_t	start;
	start = get_current_time();
	while ((get_current_time() - start) <= milliseconds)
	{
		pthread_mutex_lock(&prg->dead_lock);
		pthread_mutex_lock(&prg->full_mut);
		if (prg->is_dead == 1 || prg->full == 1)
		{
			pthread_mutex_unlock(&prg->dead_lock);
			pthread_mutex_unlock(&prg->full_mut);
			return (1);
		}
		pthread_mutex_unlock(&prg->full_mut);
		pthread_mutex_unlock(&prg->dead_lock);
		usleep(200);
	}
	return (0);
}
int give_nmeals(t_philos *philo)
{
	int n;
	
	n = 0;
	pthread_mutex_lock(&philo->program->meals_mut);
	n = philo->meals;
	pthread_mutex_unlock(&philo->program->meals_mut);
	return (n);
}

int mutex_flag(t_philos *philo)
{
	int flag;

	flag = 0;
	pthread_mutex_lock(&philo->program->dead_lock);
	flag = philo->program->is_dead;
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (flag);
}