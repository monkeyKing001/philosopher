/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:09:14 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/08 16:02:28 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

/*
 * argv[1] = number_of_philosophers 
 * argv[2] = time_to_die 
 * argv[3] = time_to_eat 
 * argv[4] = time_to_sleep 
 * argv[5] = [number_of_times_each_philosopher_must_eat] <- an optional arg
 */
int	main(int argc, char **argv)
{
	t_desk	*desk;

	if (argc != 5 && argc != 6)
		return (0);
	desk = init_desk(argc, (const char **)argv);
	if (!desk)
		return (0);
	desk -> phils = init_phils(desk);
	if (!desk -> phils)
		return (0);
	hello_philosophers(desk);
	return (0);
}

t_desk	*init_desk(int argc, const char **argv)
{
	t_desk	*desk;
	int		i;

	desk = malloc(sizeof(t_desk));
	if (!desk)
		return (NULL);
	desk -> phils_num = ft_atoi(argv[1]);
	desk -> time_to_die = ft_atoi(argv[2]);
	desk -> time_to_eat = ft_atoi(argv[3]);
	desk -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		desk -> number_of_must_eat = ft_atoi(argv[5]);
	desk -> forks = malloc(sizeof(pthread_mutex_t) * desk -> phils_num);
	desk -> info_mutex = malloc(sizeof(pthread_mutex_t));
	if (!desk -> forks || ! desk -> info_mutex)
		return (NULL);
	i = 0;
	while (i < desk -> phils_num)
		pthread_mutex_init(&desk -> forks[i++], NULL);
	pthread_mutex_init(desk -> info_mutex, NULL);
	return (desk);
}

t_philosopher	*init_phils(t_desk *desk)
{
	t_philosopher		*phils;
	int					phils_num;
	int					i;
	long long			birth_ms;

	phils_num = desk -> phils_num;
	phils = malloc(sizeof(t_philosopher) * phils_num);
	if (!phils)
		return (NULL);
	birth_ms = get_time_ms();
	i = 0;
	while (i < phils_num)
	{
		phils[i].left_fork = &desk -> forks[i % phils_num];
		phils[i].right_fork = &desk -> forks[(i + 1) % phils_num];
		phils[i].status = SLEEPING;
		phils[i].time_to_die = desk -> time_to_die;
		phils[i].time_to_eat = desk -> time_to_eat;
		phils[i].time_to_sleep = desk -> time_to_sleep;
		phils[i].num_eat = 0;
		phils[i++].last_time = birth_ms;
	}
	return (phils);
}
