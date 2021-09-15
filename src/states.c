/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/15 22:11:28 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int g_semaphore = 0;

void	remove_fork(t_info *p)
{
	*p->fork_left = false;
	*p->fork_rigth = false;
	p->st = sleeping;
}

void	stop_eating(t_info *p)
{
	if (*p->fork_left == true && *p->fork_rigth == true)
	{
		remove_fork(p);
		printf("%ld: %d is sleeping\n", get_time(), p->id);
		usleep(p->time_to_sleep);
	}
}

static	void	assign_fork(t_info *p)
{
	*p->fork_left = true;
	*p->fork_rigth = true;
	p->st = eating;
}

void	start_eating(t_info *p)
{
	long	current;

	current = get_time();
}

void	give_forks(t_info *p)
{
	if (p->time_to_die < p->time_to_eat + p->time_to_sleep)
	{
		p->st = is_dead;
		return ;
	}
	pthread_mutex_lock(&g_lock);
	if (*p->fork_left == false && *p->fork_rigth == false)
	{
		assign_fork(p);
		p->st = eating;
		printf("%ld: %d has taken a fork\n", get_time(), p->id);
		printf("%ld: %d has taken a fork\n", get_time(), p->id);
		printf("time to eat %d\n", p->time_to_eat);
		start_eating(p);
	}
	pthread_mutex_unlock(&g_lock);
}

void	think(t_info *p)
{
	p->st = thinking;
	printf("%ld: %d is thinking\n", get_time(), p->id);
}
