/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:02:01 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/31 13:02:27 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checkspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	size_t	n;
	int		tmp;

	if (!str)
		return (0);
	i = ft_checkspace(str);
	n = 0;
	tmp = 1;
	if (str[i] <= '0' || str[i] >= '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	if ((str[i] <= '0' || str[i] >= '9') && str[i] != '\0')
		return (-1);
	if (n > 2147483647 && tmp == 1)
		return (-1);
	return (n * tmp);
}
