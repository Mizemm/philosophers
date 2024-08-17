/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:27:33 by mizem             #+#    #+#             */
/*   Updated: 2024/08/12 15:49:38 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	int philos;
	int t_die;
	int t_eat;
	int t_sleep;
	if (ac == 5)
	{
		philos = ft_atoi(av[1]);
		t_die = ft_atoi(av[2]);
		t_eat = ft_atoi(av[3]);
		t_sleep = ft_atoi(av[4]);
		printf("%d, %d, %d, %d", philos, t_die, t_eat, t_sleep);
	}
}