/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:30:23 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/29 22:47:41 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_life
{
	int		number_of_philosophers;
	long	time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals;
}t_life;

typedef struct phi
{
	pthread_mutex_t	*l_increment;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*lock_nb;
	pthread_mutex_t	lockout;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_t		t_id;
	t_life			*life;
	long			last_meal;
	int				nb;
	long			t0;
	long			t1;
	int				id;
}t_phi;

typedef struct philo
{
	pthread_mutex_t	l_incr;
	pthread_mutex_t	llm;
	pthread_mutex_t	lnb;
	pthread_mutex_t	*lock;
	pthread_mutex_t	lockout;
	t_phi			*philosopher;
	long			t0;
	int				counter;
	t_life			life;
}t_philo;

void	eating(t_phi *philo);
void	handle_died(t_philo *philo, int i, int j, long var);
void	ft_error(char *error);
long	ft_time(void);
void	sleeping(t_phi *philo);
void	thinking(t_phi *philo);
void	status(t_phi *philo, char *status);
void	ft_sleep(long t);
int		ft_atoi(const char *str);
#endif
