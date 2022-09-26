/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:09:31 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/26 15:18:54 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

int	eating(t_desk *desk, int phil_idx)
{
	t_philosopher *phil;

	phil = &(desk -> phils[phil_idx]);
//	printf("time diff : %lld\n", get_time_interval(phil -> last_time, get_time_ms()));
	if (check_die(desk, phil_idx) == TRUE)
		return (0);
	if (desk -> finished == FALSE)
	{
		pthread_mutex_lock(phil -> left_fork);
		pthread_mutex_lock(phil -> right_fork);
		printf("%lld %d has taken a fork\n", get_timestamp(phil), phil_idx);
		printf("%lld %d has taken a fork\n", get_timestamp(phil), phil_idx);
		printf("%lld %d is eating\n", get_timestamp(phil), phil_idx);
		usleep((int)phil -> time_to_eat * 1000);
		phil -> last_time = get_time_ms();
		pthread_mutex_unlock(phil -> left_fork);
		pthread_mutex_unlock(phil -> right_fork);
		phil -> num_eat++;
	}
	return (1);
}

int	thinking(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (desk -> finished == FALSE)
	{
		usleep(30);
		printf("%lld %d is thinking\n", get_timestamp(phil), phil -> phils_id);
		return (1);
	}
	return (0);
}

int	sleeping(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;
	long long		time_100_ms;

	if (desk -> finished == FALSE)
	{
		phil = &(desk -> phils[phil_idx]);
		time_100_ms = 0;
		printf("%lld %d is sleeping\n", get_timestamp(phil), phil -> phils_id);
		while (check_die(desk, phil_idx) == FALSE && time_100_ms < phil -> time_to_die)
		{
			if (check_die(desk, phil_idx) == TRUE)
				return (0);
			usleep(100 * 1000);
			time_100_ms += 100;
		}
	}
	return (1);
}

int check_die(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	if (desk -> finished == FALSE && phil -> time_to_die	< \
			get_time_interval(phil -> last_time, get_time_ms()))
	{
		phil -> status = DIE;
		desk -> finished = TRUE;
		printf("%lld %d died\n", \
				get_time_interval(phil -> birth_ms, \
				get_time_ms()), phil_idx);
		return (1);
	}
	return (0);
}
