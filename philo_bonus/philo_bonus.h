/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:47:16 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/31 21:19:56 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_life
{
	long	time_to_die;
	int		number_of_philosophers;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals;
}t_life;

typedef struct phi
{
	pthread_t	t_id;
	t_life		*life;
	sem_t		*status;
	sem_t		*forks;
	long		t0;
	long		t1;
	long		last_meal;
	int			id;
	int			nb;
	int			ac;
}t_phi;

typedef struct philo
{
	long			time;
	pthread_t		died;
	t_life			life;
	t_phi			*philosopher;
	long			t0;
}t_philo;

void	routine(t_phi *philosopher);
void	kill_processes(t_philo *philo, int *p_id);
void	*handle_died(void *phi);
long	ft_time(void);
void	sleeping(t_phi *philo);
void	thinking(t_phi	*philo);
void	status(t_phi *philo, char *status);
void	ft_sleep(long t);
int		ft_atoi(const char *str);
void	ft_error(char *error);
#endif
