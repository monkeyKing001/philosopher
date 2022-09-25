/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:09:31 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/25 18:35:59 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

int	eating(t_philosopher *phil)
{
	if (phil -> time_to_die \
			< get_time_interval(phil -> last_time, get_time_ms()))
	{
		printf("%lld %d died\n", \
				get_time_interval(phil -> last_time, \
				get_time_ms()), phil-> phils_id);
		return (0);
	}
	pthread_mutex_lock(phil -> left_fork);
	pthread_mutex_lock(phil -> right_fork);
	printf("%lld %d has taken a fork\n", get_timestamp(phil), phil -> phils_id);
	phil -> last_time = get_time_ms();
	printf("%lld %d is eating\n", get_timestamp(phil), phil -> phils_id);
	phil -> last_time = get_time_ms();
	usleep((int)phil -> time_to_eat);
	pthread_mutex_unlock(phil -> left_fork);
	pthread_mutex_unlock(phil -> right_fork);
	phil -> num_eat++;
	return (1);
}

int	thinking(t_philosopher *phil)
{
	phil -> last_time = get_time_ms();
	printf("%lld %d is thinking\n", get_timestamp(phil), phil -> phils_id);
	return (1);
}

int	sleeping(t_philosopher *phil)
{
	phil -> last_time = get_time_interval(phil -> last_time, get_time_ms());
	printf("%lld %d is sleeping\n", get_timestamp(phil), phil -> phils_id);
	usleep((int)phil -> time_to_sleep * 1000);
	return (1);
}
