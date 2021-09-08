/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:43:19 by rimartin          #+#    #+#             */
/*   Updated: 2021/02/22 18:22:00 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	less_32(int c)
{
	if (c >= 32)
		return (1);
	else
		return (0);
}

static int	bigger_126(int c)
{
	if (c < 127)
		return (1);
	else
		return (0);
}

int	ft_isprint(int c)
{
	if (less_32(c) && bigger_126(c))
		return (1);
	else
		return (0);
}
