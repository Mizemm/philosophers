/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:27:33 by mizem             #+#    #+#             */
/*   Updated: 2024/09/08 23:53:40 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void join_threads(t_program *prg, int philos)
{
	int i;

	i = 0;
	while (i < philos)
	{
		pthread_join(prg->philos[i].thread, NULL);
		i++;
	}
}
int check_deads(t_program *prg, int philos)
{
	int i = 0;
	while (i < philos)
	{
		if (get_current_time() - prg->philos[i].last_meal >= prg->time_to_die)
		{
			pthread_mutex_lock(&prg->dead_lock);
			prg->is_dead = 1;
			pthread_mutex_unlock(&prg->dead_lock);
			pthread_mutex_lock(&prg->print);
			printf("%zu  %d  %s...\n", (get_current_time() - prg->start_time), prg->philos[i].id, "philo has died");
			pthread_mutex_unlock(&prg->print);
			return (1);
		}
		i++;
	}
		return (0);
}
void create_threads(t_program *prg, int philos)
{
	int i;

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
	}
}
void init_mutex(t_program **prg, int philos)
{
	int i;

	i = 0;
	(*prg)->forks = malloc(philos * sizeof(pthread_mutex_t));
	while (i < philos)
	{
		pthread_mutex_init(&(*prg)->forks[i], NULL);
		i++;
	}
}
void	give_forks(t_program **prg, int philos)
{
	int i = 0;
	if (philos == 1)
	{
		(*prg)->philos[i].l_fork = i + 1;
		(*prg)->philos[i].r_fork = -1;
	}
	else
	{
		while (i < philos)
		{
			if (philos - i == 1)
			{				
				(*prg)->philos[i].l_fork = i + 1;
				(*prg)->philos[i].r_fork = 1;
			}
			else
			{
				(*prg)->philos[i].l_fork = i + 1;
				(*prg)->philos[i].r_fork = i + 2;
			}
			i++;
		}	
	}
}
void fill_struct(t_program **prg, int ac, char **av)
{
	int i;
	
	i = 0;
	(*prg) = malloc(sizeof(t_program));
	(*prg)->num_of_philos = ft_atoi(av[1]);
	(*prg)->time_to_die = ft_atoi(av[2]);
	(*prg)->time_to_eat = ft_atoi(av[3]);
	(*prg)->time_to_sleep = ft_atoi(av[4]);
	(*prg)->start_time = get_current_time();
	(*prg)->food = -1;
	(*prg)->is_dead = 0;
	(*prg)->philos = malloc(sizeof(t_philos) * ft_atoi(av[1]));
	while (i <= ft_atoi(av[1]))
	{
		(*prg)->philos[i].id = i + 1;
		(*prg)->philos[i].program = *prg;
		
		if (ac == 6)
			(*prg)->food = ft_atoi(av[5]);
		i++;			
	}
}
int main(int ac, char **av)
{
	t_program *prg;
	
	prg = NULL;
	if (ac == 5 || ac == 6)
	{
		fill_struct(&prg, ac, av);
		give_forks(&prg, ft_atoi(av[1]));
		init_mutex(&prg, ft_atoi(av[1]));
		create_threads(prg, ft_atoi(av[1]));
		join_threads(prg, ft_atoi(av[1]));
		// printf("num of philos : %d\ntime to die : %d\ntime to eat : %d\ntime to sleep : %d\nfood : %d\n", 
		// 		prg->num_of_philos, prg->time_to_die, prg->time_to_eat, prg->time_to_sleep, prg->food);
	}
} 