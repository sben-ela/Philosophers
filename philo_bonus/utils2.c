/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:37:26 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/31 21:24:34 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(char *error)
{
	printf("\033[4;31m ERROR : %s \n", error);
	exit(0);
}

void	*handle_died(void *phi)
{
	t_phi	*philosopher;
	long	time;

	philosopher = (t_phi *)phi;
	while (1)
	{
		if (ft_time() - philosopher->last_meal > philosopher->life->time_to_die)
		{
			time = ft_time() - philosopher->t0;
			sem_wait(philosopher->status);
			printf("\033[0;31m%ld ms : %d %s\n", time,
				philosopher->id, " : is died");
			exit (1);
		}
	}
}

void	kill_processes(t_philo *philo, int *p_id)
{
	int	j;
	int	exit;

	j = 0;
	while (j < philo->life.number_of_philosophers)
	{
		waitpid(-1, &exit, 0);
		if (exit != 0)
		{
			j = 0;
			free(p_id);
			while (j < philo->life.number_of_philosophers)
			{
				kill(p_id[j++], SIGKILL);
			}
		}
		j++;
	}
}
