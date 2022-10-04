/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:09:14 by dokwak            #+#    #+#             */
/*   Updated: 2022/10/04 23:01:00 by dokwak           ###   ########.fr       */
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

	if (error_arg_check(argc, argv) == FAIL)
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
	desk -> number_of_must_eat = 2147483647;
	if (argc == 6)
		desk -> number_of_must_eat = ft_atoi(argv[5]);
	desk -> finished = FALSE;
	desk -> forks = malloc(sizeof(pthread_mutex_t) * desk -> phils_num);
	if (!desk -> forks)
		return (NULL);
	i = 0;
	while (i < desk -> phils_num)
		pthread_mutex_init(&desk -> forks[i++], NULL);
	pthread_mutex_init(&(desk -> info_mutex), NULL);
	pthread_mutex_init(&(desk -> desk_die_mutex), NULL);
	pthread_mutex_init(&(desk -> print_mutex), NULL);
	return (desk);
}

t_philosopher	*init_phils(t_desk *desk)
{
	t_philosopher		*phils;
	long long			birth_ms;
	int					phils_num;
	int					i;

	phils_num = desk -> phils_num;
	birth_ms = get_time_ms();
	phils = malloc(sizeof(t_philosopher) * phils_num);
	if (!phils)
		return (NULL);
	i = 0;
	while (i < phils_num)
	{
		phils[i].desk = desk;
		phils[i].left_fork = &desk -> forks[i % phils_num];
		phils[i].right_fork = &desk -> forks[(i + 1) % phils_num];
		phils[i].time_to_die = desk -> time_to_die;
		phils[i].time_to_eat = desk -> time_to_eat;
		phils[i].time_to_sleep = desk -> time_to_sleep;
		phils[i].num_eat = 0;
		phils[i].birth_ms = birth_ms;
		phils[i].last_time = phils[i].birth_ms;
		phils[i++].max_eat_num = desk -> number_of_must_eat;
	}
	return (phils);
}

int	error_arg_check(int argc, char **argv)
{
	int	i;
	int	argv_idx;

	if (argc != 5 && argc != 6)
	{
		printf("Error : unvalid argument count\n");
		return (0);
	}
	argv_idx = 1;
	i = 0;
	while (argv_idx < argc)
	{
		i = 0;
		while (argv[argv_idx][i])
		{
			if (!ft_isdigit((const char)argv[argv_idx][i]))
			{
				printf("Error : unvalid argument value");
				return (0);
			}
			i++;
		}
		argv_idx++;
	}
	return (1);
}

int	single_phil_case(t_desk *desk)
{
	print_state(desk, 0, FORK);
	time_passing(desk -> time_to_die);
	print_state(desk, 0, DIED);
	pthread_mutex_destroy(&desk -> forks[0]);
	free(desk -> phils);
	pthread_mutex_destroy(&desk -> desk_die_mutex);
	pthread_mutex_destroy(&desk -> info_mutex);
	pthread_mutex_destroy(&desk -> print_mutex);
	return (1);
}
