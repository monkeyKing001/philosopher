/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:13:24 by dokwak            #+#    #+#             */
/*   Updated: 2022/08/30 18:59:46 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SLEEPING 0
# define THINKING 1
# define EATING 2
# define DIE 4
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

/*
** SLEEPING = 0
** EATING = 1
** THINKING = 2
*/
typedef struct s_philosopher
{
	char				status;
	unsigned long long	last_time;
}	t_philosopher;

/*
** fork = 0 -> occupied now
** fork = 1 -> available now
*/
typedef struct s_desk
{
	t_philosopher		*phils;
	char				*fork;
	int					phils_num;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					number_of_must_eat;
}	t_desk;

int				ft_atoi(const char *s);
t_desk			*init_desk(int argc, const char **argv);
t_philosopher	*init_phils(int phils_num);
void			report_status(int phil, int status);
long long		get_time_ms(void);
#endif
