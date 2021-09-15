/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:03 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/15 22:11:16 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
{
	struct	timeval beg;
	static	int	i;
	
	if (i++ == 0)
		gettimeofday(&start_time, NULL);
	gettimeofday(&beg, NULL);
	
	return (((beg.tv_sec - start_time.tv_sec) * 1000) \
	+ ((beg.tv_usec - start_time.tv_usec) / 1000));
}