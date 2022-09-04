/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:44:39 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/04 21:25:33 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"
/*
** concatenate src to dest	
** dest = abc ,  src = def 
** after strlcat(dest, src, 7);
** dest -> abcdef																
**
** case 1)  failed to cat 	
** 		->	destsize < dest
**		->	no concatenate
**		->	return (len(src) + destsize);
**
** case 2)  partially failed to cat
** 		->	destsize < dest + (n of src)		
**		->	partial concatenate
**		->	return (len(dest) + len(src));
**
** case 3) succeed to cat
**		->	destsize > dest + (n of src) 
**		->	fully concatenate
**		->	return (len(dest) + len(src));
*/
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*dest && i < dstsize)
	{
		++i;
		++dest;
	}
	while (*src && i + 1 < dstsize)
	{
		*dest = *src;
		++dest;
		++src;
		++i;
	}
	if (i < dstsize)
		*dest = 0;
	while (*src)
	{
		++i;
		++src;
	}
	return (i);
}
