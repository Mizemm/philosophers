/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:09:42 by mizem             #+#    #+#             */
/*   Updated: 2024/09/08 15:55:42 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void  is_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}

void is_print(t_philos *philo, char *str)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->is_dead == 0)
	{
		pthread_mutex_lock(&philo->program->print);
		printf("%zu  %d  %s...\n", (get_current_time() - philo->program->start_time), philo->id, str);
		pthread_mutex_unlock(&philo->program->print);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
}

void is_sleeping(t_philos *philo)
{
	is_print(philo, "Is Sleeping");
	is_usleep(philo->program->time_to_sleep);
}

void is_thinking(t_philos *philo)
{
	is_print(philo, "Is Thinking");
}
void is_eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
	is_print(philo, "philo has take a fork");
	pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
	is_print(philo, "philo has take a fork");
	philo->last_meal = get_current_time();
	is_print(philo, "Is Eating");
	is_usleep(philo->program->time_to_eat);
	pthread_mutex_unlock(&philo->program->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->l_fork]);
}

void *routine(void *param)
{
	t_philos *philo;
	
	philo = param;
	is_thinking(philo);
	if (philo->id % 2 != 0)
		is_usleep(philo->program->time_to_sleep);
	while (1)
	{
		pthread_mutex_lock(&philo->program->dead_lock);
		if(philo->program->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->program->dead_lock);
			break;
		}
		pthread_mutex_unlock(&philo->program->dead_lock);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
		
	}
	return (NULL);
}