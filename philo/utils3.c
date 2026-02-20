/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:25:28 by mizem             #+#    #+#             */
/*   Updated: 2024/09/17 23:43:26 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_routine(void *param)
{
	t_philos	*philo;

	philo = param;
	pthread_mutex_lock(&philo->program->forks[0]);
	is_print(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->program->forks[0]);
	is_usleep(philo->program->time_to_die, philo->program);
	printf("%zu %d %s\n", (get_current_time()
			- philo->program->start_time),
		philo->program->philos[0].id, "died");
	return (NULL);
}

int	special_one(t_program *prg)
{
	pthread_create(&prg->philos[0].thread, NULL, &one_routine, &prg->philos[0]);
	pthread_join(prg->philos[0].thread, NULL);
	return (1);
}

void	clear_all(t_program *prg)
{
	int	i;

	i = 0;
	while (i < prg->num_of_philos)
	{
		pthread_mutex_destroy(&prg->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prg->print);
	pthread_mutex_destroy(&prg->dead_lock);
	pthread_mutex_destroy(&prg->last_meal_mut);
	pthread_mutex_destroy(&prg->meals_mut);
	pthread_mutex_destroy(&prg->full_mut);
	free(prg->forks);
	free(prg->philos);
	free(prg);
}
