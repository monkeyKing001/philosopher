/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:09:14 by dokwak            #+#    #+#             */
/*   Updated: 2022/08/30 19:34:19 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

/*
** argv[1] = number_of_philosophers 
** argv[2] = time_to_die 
** argv[3] = time_to_eat 
** argv[4] = time_to_sleep 
** argv[5] = [number_of_times_each_philosopher_must_eat] <- an optional arg
*/
int	main(int argc, char **argv)
{
	struct timeval		unix;
	struct tm			*date;
	t_desk				*desk;
	unsigned long long	u_test_ms;
	long long			test_ms;

	if (argc != 5 && argc != 6)
		return (0);
	desk = malloc(sizeof(t_desk));
	desk = init_desk(argc, (const char **)argv);
	if (!desk)
		return (0);
	if (gettimeofday(&unix, NULL) == -1)
		return (1);
	date = localtime(&(unix.tv_sec));
	printf("Unix Time: %ld\t%d\n", unix.tv_sec, unix.tv_usec);
	printf("\n##############################\n");
	printf("####### testing ms time ######\n");
	printf("##############################\n\n");
	u_test_ms = (unix.tv_sec * 1000) + (unix.tv_usec / 1000);
	test_ms = (unix.tv_sec * 1000) + (unix.tv_usec / 1000);
	printf("unsigned long long ms = %lld\n", u_test_ms);
	printf("long long ms = %lld\n", test_ms);
	//system("leaks philo");
	return (0);
}

t_desk	*init_desk(int argc, const char **argv)
{
	t_desk	*desk;
	int		phils_num;

	phils_num = ft_atoi(argv[1]);
	desk = malloc(sizeof(t_desk));
	if (!desk)
		return (NULL);
	desk -> phils_num = phils_num;
	desk -> fork = malloc(sizeof(char) * phils_num);
	if (!desk -> fork)
		return (NULL);
	memset(desk -> fork, 1, sizeof(char) * phils_num);
	desk -> phils = init_phils(phils_num);
	if (!desk -> phils)
		return (NULL);
	desk -> time_to_die = ft_atoi(argv[2]);
	desk -> time_to_eat = ft_atoi(argv[3]);
	desk -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		desk -> number_of_must_eat = ft_atoi(argv[5]);
	return (desk);
}

t_philosopher	*init_phils(int phils_num)
{
	t_philosopher	*phils;
	int				i;

	phils = malloc(sizeof(t_philosopher) * phils_num);
	if (!phils)
		return (NULL);
	i = 0;
	while (i < phils_num)
	{
		phils[i].status = SLEEPING;
		phils[i++].last_time = 0;
	}
	return (phils);
}
