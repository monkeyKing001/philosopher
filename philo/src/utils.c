/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:58:43 by dokwak            #+#    #+#             */
/*   Updated: 2022/10/01 22:52:54 by dokwak           ###   ########.fr       */
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

void	time_passing(long long time)
{
	long long	end_time;

	end_time = time + get_time_ms();
	while (end_time > get_time_ms())
		usleep(10);
}

void	print_state(t_desk *desk, int phil_idx, int STATUS)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (STATUS == SLEEPING && check_die_desk(desk, phil_idx, CHECK) == FALSE)
		printf("%lld %d is sleeping\n", get_timestamp(phil), phil_idx + 1);
	else if (STATUS == THINKING \
			&& check_die_desk(desk, phil_idx, CHECK) == FALSE)
		printf("%lld %d is thinking\n", get_timestamp(phil), phil_idx + 1);
	else if (STATUS == FORK && check_die_desk(desk, phil_idx, CHECK) == FALSE)
		printf("%lld %d has taken a fork\n", get_timestamp(phil), phil_idx + 1);
	else if (STATUS == EATING && check_die_desk(desk, phil_idx, CHECK) == FALSE)
		printf("%lld %d is eating\n", get_timestamp(phil), phil_idx + 1);
	else if (STATUS == DIED && check_die_desk(desk, phil_idx, CHECK) == FALSE)
		printf("%lld %d died\n", \
				get_time_interval(phil -> birth_ms, \
				get_time_ms()), phil_idx + 1);
}
