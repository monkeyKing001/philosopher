/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:21:47 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/30 18:35:29 by dokwak           ###   ########.fr       */
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
void	hello_philosophers(t_desk *desk)
{
	int				i;
	int				offset;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * desk -> phils_num);
	offset = desk -> phils_num + (desk -> phils_num % 2 == 0);
	i = 1;
	while (pthread_mutex_lock(&(desk-> info_mutex)) == 0 \
			&& i < (desk -> phils_num * 2) + 1)
	{
		//write
		desk -> phils_idx = i % offset;
		desk -> phils[i % offset].phils_id = i % offset;
		pthread_create(&threads[i % offset], NULL, \
				philosophers_action, (void *)(desk));
		i += 2;
	}
	bye_philosophers(desk, threads);
}

void	*philosophers_action(void *v_desk)
{
	t_desk			*desk;
	int				phil_idx;

	desk = v_desk;
	// read
	phil_idx = desk -> phils_idx;
	pthread_mutex_unlock(&(desk -> info_mutex));
	philosophers_action_2(desk, phil_idx);
	return (NULL);
}

int	philosophers_action_2(t_desk *desk, int phil_idx)
{
	t_philosopher	*phil;

	phil = &(desk -> phils[phil_idx]);
	pthread_mutex_init(&(phil -> desk_die_mutex), NULL);
	while (check_die_desk(desk, CHECK) == FALSE && \
			check_full(desk, phil_idx) == FALSE)
	{
		eating(desk, phil_idx);
		sleeping(desk, phil_idx);
		thinking(desk, phil_idx);
	}
	return (1);
}

int	check_die_desk(t_desk *desk, int option)
{
	pthread_mutex_lock(&(desk -> desk_die_mutex));
	if (option == CHECK)
	{
		usleep(500);
		if (desk -> finished == TRUE)
		{
			pthread_mutex_unlock(&(desk -> desk_die_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(desk -> desk_die_mutex));
		return (0);
	}
	else if (option == UPDATE)
		desk -> finished = TRUE;
	pthread_mutex_unlock(&(desk -> desk_die_mutex));
	return (1);
}

void	bye_philosophers(t_desk *desk, pthread_t *threads)
{
	int				i;
	int				offset;

	offset = desk -> phils_num + (desk -> phils_num % 2 == 0);
	i = 1;
	while (i < (desk -> phils_num * 2) + 1)
	{
		pthread_join(threads[i % offset], NULL);
		i += 2;
	}
}
