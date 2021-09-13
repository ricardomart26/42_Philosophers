/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:03 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/13 15:50:04 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
{
	static	struct	timeval current;
	struct	timeval beg;
	static	int	i;
	
	if (i++ == 0)
		gettimeofday(&current, NULL);
	gettimeofday(&beg, NULL);
	
	return (((beg.tv_sec - current.tv_sec) * 1000) \
	+ ((beg.tv_usec - current.tv_usec) / 1000));
}