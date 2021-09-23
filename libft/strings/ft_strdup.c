/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:32 by rimartin          #+#    #+#             */
/*   Updated: 2021/02/23 16:28:38 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		size;

	size = ft_strlen((char *)s1);
	dup = (char *)malloc(size + 1);
	if (!dup)
		return (NULL);
	while (*s1)
	{
		*dup = *(char *)s1;
		s1++;
		dup++;
	}
	*dup = '\0';
	return (dup - size);
	free(dup);
}
