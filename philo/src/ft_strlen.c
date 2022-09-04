/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:22:00 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/04 21:26:24 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	ret_size;

	ret_size = 0;
	while (str[ret_size])
		ret_size++;
	return (ret_size);
}
