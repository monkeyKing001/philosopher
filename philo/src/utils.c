/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:58:43 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/19 10:05:31 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time_ms(void)
{
	struct timeval	start_time;
	long long		time_ms;

	gettimeofday(&start_time, NULL);
	time_ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return (time_ms);
}

long long	get_time_interval(long long start, long long end)
{
	return (end - start);
}

long long	get_timestamp(t_philosopher *phil)
{
	long long	timestamp;

	timestamp = get_time_ms() - phil -> birth_ms;
	return (timestamp);
}
