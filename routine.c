/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:09:42 by mizem             #+#    #+#             */
/*   Updated: 2024/09/13 17:41:13 by mizem            ###   ########.fr       */
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
void	*one_routine(void *param)
{
	t_philos *philo;

	philo = param;
	pthread_mutex_lock(&philo->program->forks[0]);
	is_print(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->program->forks[0]);
	is_usleep(philo->program->time_to_die, philo->program);
	printf("%zu %d %s\n", (get_current_time() - philo->program->start_time), philo->program->philos[0].id, "died");
	return (NULL);
}
int special_one(t_program *prg)
{
	pthread_create(&prg->philos[0].thread, NULL, &one_routine, &prg->philos[0]);
	pthread_join(prg->philos[0].thread, NULL);
	return (1);
}