/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/13 15:55:12 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int g_semaphore = 0;

void	remove_fork(t_info *p)
{
	pthread_mutex_lock(&g_lock);
	p->st = sleeping;
	pthread_mutex_unlock(&g_lock);
}

void	stop_eating(t_info *p)
{
	pthread_mutex_lock(&p->fork_left);
	pthread_mutex_lock(&p->fork_rigth);
}

static	void	assign_fork(t_info *p)
{

	p->st = eating;
	usleep(p->time_to_eat);
}

void	give_forks(t_info *p)
{
	static int i = 0;
	if (p->time_to_die < p->time_to_eat + p->time_to_sleep)
	{
		p->st = is_dead;
		return ;
	}
	if (p->id % i == 0)
	{
		pthread_mutex_lock(&p->fork_left);
		pthread_mutex_lock(&p->fork_rigth);
		assign_fork(p);
		printf("%ld: %d has taken a fork\n", get_time(), p->id);
		printf("%ld: %d has taken a fork\n", get_time(), p->id);
		pthread_mutex_unlock(&p->fork_left);
		pthread_mutex_unlock(&p->fork_rigth);
		usleep(p->time_to_eat);
	}
}

void	think(t_info *p)
{
	p->st = thinking;
}
