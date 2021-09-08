/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/08 05:58:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	remove_fork(t_info *p)
{
	pthread_mutex_lock(&p->lock);
	*p->fork_left = false;
	*p->fork_right = false;
	p->st = sleeping;
	pthread_mutex_unlock(&p->lock);
}

void	stop_eating(t_info *p, long time)
{
	(void)time;

	if (*p->fork_left == true && *p->fork_right == true)
	{
		// printf("%ld: %d has released a fork\n", time, p->id);
		// printf("%ld: %d has released a fork\n", time, p->id);
		remove_fork(p);
		printf("%ld: %d is sleeping\n", time, p->id);
		usleep(p->time_to_sleep);

	}
}


static	void	assign_fork(t_info *p)
{
	*p->fork_left = true;
	*p->fork_right = true;
	p->st = eating;
	usleep(p->time_to_eat);
}

void	give_forks(t_info *p, long time)
{
	// printf("id %d\n", p->id);
	pthread_mutex_lock(&p->lock);
	if (*p->fork_left == false && *p->fork_right == false)
	{
		pthread_mutex_lock(&p->lock2);
		assign_fork(p);
		printf("%ld: %d has taken a fork\n", time, p->id);
		printf("%ld: %d has taken a fork\n", time, p->id);
		usleep(p->time_to_eat);
		pthread_mutex_unlock(&p->lock2);
	}
	pthread_mutex_unlock(&p->lock);
}

void	think(t_info *p, long time)
{
	(void)time;
	p->st = thinking;
	printf("%ld: %d is thinking\n", time, p->id);
}
