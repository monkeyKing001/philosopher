/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:09:31 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/30 16:46:58 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

int	eating(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (check_die(desk, phil_idx) == TRUE || check_full(desk, phil_idx) == TRUE)
		return (0);
	pthread_mutex_lock(phil -> left_fork);
	pthread_mutex_lock(phil -> right_fork);
	if (check_die_desk(desk, CHECK) == FALSE)
	{
		printf("%lld %d has taken a fork\n", get_timestamp(phil), phil_idx + 1);
		printf("%lld %d has taken a fork\n", get_timestamp(phil), phil_idx + 1);
		printf("%lld %d is eating\n", get_timestamp(phil), phil_idx + 1);
		phil -> last_time = get_time_ms();
		usleep((int)phil -> time_to_eat * 1000);
		pthread_mutex_unlock(phil -> left_fork);
		pthread_mutex_unlock(phil -> right_fork);
		phil -> num_eat++;
		return (1);
	}
	else
	{
		pthread_mutex_unlock(phil -> left_fork);
		pthread_mutex_unlock(phil -> right_fork);
		return (0);
	}
}

int	thinking(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (check_die_desk(desk, CHECK) == FALSE)
	{
		printf("%lld %d is thinking\n", get_timestamp(phil), phil_idx + 1);
		return (1);
	}
	return (0);
}

int	sleeping(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;
	long long		time_10_ms;

	phil = &(desk -> phils[phil_idx]);
	if (check_die_desk(desk, CHECK) == FALSE)
	{
		time_10_ms = 0;
		printf("%lld %d is sleeping\n", get_timestamp(phil), phil_idx + 1);
		while (check_die(desk, phil_idx) == FALSE && \
				time_10_ms < phil -> time_to_sleep)
		{
			if (check_die(desk, phil_idx) == TRUE)
				return (0);
			usleep(10 * 1000);
			time_10_ms += 10;
		}
	}
	return (1);
}

int	check_die(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (check_die_desk(desk, CHECK) == FALSE \
			&& phil -> time_to_die \
			< get_time_interval(phil -> last_time, get_time_ms()))
	{
		check_die_desk(desk, UPDATE);
		phil -> status = FINISHED;
		usleep(500);
		printf("%lld %d died\n", \
				get_time_interval(phil -> birth_ms, \
				get_time_ms()), phil_idx + 1);
		return (1);
	}
	pthread_mutex_unlock(&(phil -> desk_die_mutex));
	return (0);
}

int	check_full(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (phil -> max_eat_num == phil -> num_eat)
	{
		phil -> status = FINISHED;
		return (1);
	}
	return (0);
}
