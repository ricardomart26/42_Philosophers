/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:03 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/23 23:57:54 by rimartin         ###   ########.fr       */
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

long	check_death_while_eating(t_info *p)
{
	long	time_passed;

	time_passed = 0;
	while (time_passed <= g_args.time_to_eat)
		time_passed = check_death(time_passed, p);
	return (time_passed);
}

long	check_death_while_sleeping(t_info *p, long time_passed)
{
	long	counter;

	counter = 0;
	while (counter <= g_args.time_to_sleep)
	{
		if (counter + time_passed >= g_args.time_to_die)
		{
			pthread_mutex_lock(&g_lock_write);
			p->st = is_dead;
			printf("%ld: %d is dead\n", get_time(), p->id);
			exit(0);
		}
		usleep(7);
		counter += 10;
	}
	return (counter + time_passed);
}
