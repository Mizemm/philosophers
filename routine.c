/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:09:42 by mizem             #+#    #+#             */
/*   Updated: 2024/09/13 22:26:15 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void is_print(t_philos *philo, char *str)
{
	int flag;
	
	flag = mutex_flag(philo);
	if (flag == 0)
	{
		pthread_mutex_lock(&philo->program->print);
		printf("%zu %d %s\n", (get_current_time() - philo->program->start_time), philo->id, str);
		pthread_mutex_unlock(&philo->program->print);
	}
}

int is_sleeping(t_philos *philo)
{
	is_print(philo, "is sleeping");
	if (is_usleep(philo->program->time_to_sleep, philo->program) == 1)
		return (1);
	return (0);
}

void is_thinking(t_philos *philo)
{
	is_print(philo, "is thinking");
}
int is_eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
	is_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
	is_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->program->last_meal_mut);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->program->last_meal_mut);
	is_print(philo, "is eating");
	pthread_mutex_lock(&philo->program->meals_mut);
	philo->meals += 1;
	pthread_mutex_unlock(&philo->program->meals_mut);
	// printf("<%d>\n", philo->meals);
	if (is_usleep(philo->program->time_to_eat, philo->program) == 1)
		return (pthread_mutex_unlock(&philo->program->forks[philo->l_fork]),
			pthread_mutex_unlock(&philo->program->forks[philo->r_fork]), 1);
	pthread_mutex_unlock(&philo->program->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->r_fork]);
	return (0);
}
void *routine(void *param)
{
	t_philos *philo;
	
	philo = param;
	if (philo->id % 2 != 0)
		is_sleeping(philo);
	while (1)
	{
		is_thinking(philo);
		if (is_eating(philo) == 1 || is_sleeping(philo) == 1)
			break ;
		is_thinking(philo);
		usleep(250);
	}
	return (NULL);
}
