/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:09:42 by mizem             #+#    #+#             */
/*   Updated: 2024/09/08 23:56:10 by mizem            ###   ########.fr       */
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
	size_t	start;
	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&prg->dead_lock);
		if (prg->is_dead == 1)
		{
			pthread_mutex_unlock(&prg->dead_lock);
			exit (1);
		}
		pthread_mutex_unlock(&prg->dead_lock);
		usleep(200);
	}
	return (0);
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

void is_print(t_philos *philo, char *str)
{
	int flag;
	
	flag = mutex_flag(philo);
	if (flag == 0)
	{
		pthread_mutex_lock(&philo->program->print);
		printf("%zu  %d  %s...\n", (get_current_time() - philo->program->start_time), philo->id, str);
		pthread_mutex_unlock(&philo->program->print);
	}
	
}

void is_sleeping(t_philos *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->is_dead == 1)
		exit (1);
	pthread_mutex_unlock(&philo->program->dead_lock);
	is_print(philo, "Is Sleeping");
	is_usleep(philo->program->time_to_sleep, philo->program);
}

void is_thinking(t_philos *philo)
{
	is_print(philo, "Is Thinking");
}
void is_eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		exit (1);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
	is_print(philo, "philo has take a fork");
	pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
	is_print(philo, "philo has take a fork");
	philo->last_meal = get_current_time();
	is_print(philo, "Is Eating");
	is_usleep(philo->program->time_to_eat, philo->program);
	pthread_mutex_unlock(&philo->program->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->l_fork]);
}

void *routine(void *param)
{
	t_philos *philo;
	
	philo = param;
	if (philo->id % 2 != 0)
		is_sleeping(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->program->dead_lock);
		if(philo->program->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->program->dead_lock);
			break;
		}
		pthread_mutex_unlock(&philo->program->dead_lock);
		is_thinking(philo);
		is_eating(philo);
		is_sleeping(philo);
		usleep(200);
	}
	return (NULL);
}