/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:41:45 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/13 15:47:57 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	g_kill = 0;

// void	init_forks(int i, t_info **philo, int last, t_philo *p)
// {
// 	if (i == 0)
// 	{
// 		philo[i]->fork_left = p->forks[i];
// 		philo[i]->fork_right = p->forks[last];
// 	}
// 	else
// 	{
// 		philo[i]->fork_right = p->forks[i - 1];
// 		philo[i]->fork_left = p->forks[i];
// 	}
// }

void	init_mutex(void)
{
	g_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
 	g_lock2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
 	g_write_kill = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
 	g_lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void	init_philo(t_philo *p, char **av, int ac)
{
	int		i;
	long	time;

	time = get_time();
	p->nmr_p = ft_atoi(av[1]);
	p->philo = ft_calloc(p->nmr_p, sizeof(t_info));
	if (p->philo == NULL)
		return ;
	p->forks = ft_calloc(p->nmr_p, sizeof(bool));
	init_mutex();
	i = -1;
	
	while (++i < p->nmr_p)
	{
		if (ac == 6)
			p->philo[i].how_many_times_to_eat = ft_atoi(av[5]);
		else
			p->philo[i].how_many_times_to_eat = 0;
		p->philo[i].start_time = time;
		p->philo[i].id = i + 1;
		p->philo[i].time_to_die = ft_atoi(av[2]);
		p->philo[i].time_to_eat = ft_atoi(av[3]);
		p->philo[i].time_to_sleep = ft_atoi(av[4]);
		p->philo[i].st = scratch_balls;
		p->philo[i].fork_left = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		p->philo[i].fork_rigth = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	}
}
