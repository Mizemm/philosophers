/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:46:53 by mizem             #+#    #+#             */
/*   Updated: 2024/09/16 17:43:23 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_negative(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	if (is_negative(str) == 1)
		exit(1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (is_valid(str[i]) == 0)
			exit(1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX || ft_strlen(str) > 10)
		exit(1);
	return (result);
}
