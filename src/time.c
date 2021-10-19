/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:03 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/19 17:34:47 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	beg;
	static int		i;

	if (i++ == 0)
		gettimeofday(&g_start_time, NULL);
	gettimeofday(&beg, NULL);
	return (((beg.tv_sec - g_start_time.tv_sec) * 1000) \
	+ ((beg.tv_usec - g_start_time.tv_usec) / 1000));
}

int	check_death_while_eating(t_info *p)
{
	while (get_time() - p->started_eating <= g_args.time_to_eat)
	{
		if (get_time() - p->started_eating >= g_args.time_to_die)
		{
			pthread_mutex_lock(&g_lock_write);
			p->st = is_dead;
			g_args.kill = 1;
			printf("%ld: %d is dead\n", get_time(), p->id);
			return (-1);
		}
	}
	return (0);
}

int	check_death_while_sleeping(t_info *p)
{
	while (get_time() - p->started_sleeping <= g_args.time_to_sleep)
	{
		if (get_time() - p->started_eating >= g_args.time_to_die)
		{
			pthread_mutex_lock(&g_lock_write);
			p->st = is_dead;
			g_args.kill = 1;
			printf("%ld: %d is dead\n", get_time(), p->id);
			return (-1);
		}
	}
	if (g_args.kill == 1)
		return (-1);
	return (0);
}

int	check_death(t_info *p)
{
	if (get_time() - p->started_eating >= g_args.time_to_die)
	{
		p->st = is_dead;
		printer(p->id, p->st);
		if (g_args.kill == 1)
			return (-1);
		g_args.kill = 1;
		return (-1);
	}
	return (0);
}
