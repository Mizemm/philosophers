/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:21:41 by mizem             #+#    #+#             */
/*   Updated: 2024/09/16 18:06:06 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_deads(t_program *prg, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		pthread_mutex_lock(&prg->last_meal_mut);
		if (get_current_time() - prg->philos[i].last_meal >= prg->time_to_die)
		{
			pthread_mutex_lock(&prg->dead_lock);
			prg->is_dead = 1;
			pthread_mutex_unlock(&prg->dead_lock);
			pthread_mutex_lock(&prg->print);
			printf("%zu %d %s\n", (get_current_time() 
					- prg->start_time), prg->philos[i].id, "died");
			pthread_mutex_unlock(&prg->print);
			pthread_mutex_unlock(&prg->last_meal_mut);
			return (1);
		}
		pthread_mutex_unlock(&prg->last_meal_mut);
		i++;
	}
	return (0);
}

int	times_eaten(t_program *prg, int philos)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (i < philos)
	{
		if (prg->philos[i].meals >= prg->food)
			nb += 1;
		i++;
	}
	return (nb);
}

int	check_fulls(t_program *prg, int philos)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < philos)
	{
		if (give_nmeals(&prg->philos[i]) < prg->food)
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}

void	join_threads(t_program *prg, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		pthread_join(prg->philos[i].thread, NULL);
		i++;
	}
}

void	create_threads(t_program *prg, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		pthread_create(&prg->philos[i].thread, NULL, &routine, &prg->philos[i]);
		i++;
	}
	while (1)
	{
		if (check_deads(prg, philos) == 1)
			break ;
		if (prg->food != -1 && check_fulls(prg, prg->num_of_philos)
			== 1 && times_eaten(prg, philos) >= prg->num_of_philos)
		{
			pthread_mutex_lock(&prg->full_mut);
			prg->full = 1;
			pthread_mutex_unlock(&prg->full_mut);
			break ;
		}
		usleep(50);
	}
}
