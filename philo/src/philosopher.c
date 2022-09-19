/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:21:47 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/14 19:10:30 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

/*
 * odd_phils_num
 * i
 * 0 1 2 3 4(5)
 * e_i
 * 1 3 5 7 9
 * % phils_num
 * 1 3 0 2 4
 *
 * even_phils_num
 * i
 * 0 1 2 3 4 5 (6 + 1)
 * e_i 
 * 1 3 5 7 9 11
 * % phils_num + 1 = 7
 * 1 3 5 0 2 4
 * 0 
 */
//		pthread_create(&threads[i % offset], NULL, 
//			philosophers_action_2, (void *)(&desk -> phils[i % offset]));
void	hello_philosophers(t_desk *desk)
{
	int				i;
	int				offset;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * desk -> phils_num);
	offset = desk -> phils_num + (desk -> phils_num % 2 == 0);
	i = 1;
	while (i < (desk -> phils_num * 2) + 1)
	{
		pthread_mutex_lock(desk -> info_mutex);
		desk -> phils_idx = i % offset;
		desk -> phils[i % offset].phils_id = i % offset;
		pthread_create(&threads[i % offset], NULL, \
				philosophers_action, (void *)(desk));
		i += 2;
	}
	i = 1;
	while (i < (desk -> phils_num * 2) - 1)
	{
		pthread_join(threads[i % offset], NULL);
		i += 2;
	}
}

void	*philosophers_action(void *v_desk)
{
	t_desk			*desk;
	int				phil_idx;

	desk = v_desk;
	phil_idx = desk -> phils_idx;
	pthread_mutex_unlock(desk -> info_mutex);
	eating(&(desk -> phils[phil_idx]));
	return (NULL);
}
