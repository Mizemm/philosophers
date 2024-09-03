/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:09:42 by mizem             #+#    #+#             */
/*   Updated: 2024/09/03 11:30:30 by mizem            ###   ########.fr       */
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
void is_sleeping(t_philos *philo)
{
	printf("%zu %d is sleeping..\n", get_current_time(), philo->id);
	is_usleep(philo->program->time_to_sleep);
}

void is_thinking(t_philos *philo)
{
	printf("%zu %d is thinking..\n", get_current_time(), philo->id);
}

void *routine(void *param)
{
	t_philos *philo;
	
	philo = param;
	is_thinking(philo);
	if (philo->id % 2 != 0)
		is_usleep(philo->program->time_to_sleep);
	return (NULL);
}