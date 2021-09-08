/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:03 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/08 05:58:04 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
{
	long time;
	struct timeval t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec/1000);
	return (time);
}

long	calculate_time(long	time)
{
	long time2;
	long diff;

	time2 = get_time();
	diff = time2 - time;
	return (diff);
}

