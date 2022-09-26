/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:13:24 by dokwak            #+#    #+#             */
/*   Updated: 2022/09/26 14:31:12 by dokwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/***********************/
/*****  DEF_STAT  ******/
/***********************/
# define SLEEPING 0
# define THINKING 1
# define EATING 2
# define DIE 4

/***********************/
/******  BOOLEAN  ******/
/***********************/
# define FALSE 0
# define TRUE 1
# define FAIL 0
# define SUCCESS 1

/***********************/
/******  COLORS   ******/
/***********************/
# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

/***********************/
/*****  HEADERS   ******/
/***********************/
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

/*
 * SLEEPING = 0
 * EATING = 1
 * THINKING = 2
 */
typedef struct s_philosopher
{
	char				status;
	long long			birth_ms;
	long long			last_time;
	int					phils_id;
	int					num_eat;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
}	t_philosopher;

/*
 * fork = 0 -> occupied now
 * fork = 1 -> available now
 */
typedef struct s_desk
{
	t_philosopher		*phils;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*info_mutex;
	int					phils_num;
	int					phils_idx;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					number_of_must_eat;
	int					finished;
}	t_desk;

/***********************/
/*****   main.c   ******/
/***********************/
t_desk			*init_desk(int argc, const char **argv);
t_philosopher	*init_phils(t_desk *desk);
int				init_argv(t_desk *desk, int arc, const char **argv);
void			report_status(int phil, int status);

/***********************/
/*****   utils.c   *****/
/***********************/
long long		get_time_ms(void);
long long		get_time_interval(long long start, long long end);
long long		get_timestamp(t_philosopher *phil);

/***********************/
/*****    ft_*.c   *****/
/***********************/
int				ft_atoi(const char *s);
size_t			ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t			ft_strlen(char *str);

/***********************/
/**   philosopher.c  ***/
/***********************/
void			hello_philosophers(t_desk *desk);
void			bye_philosophers(t_desk *desk);
void			*philosophers_action(void *_NULLABLE);
int				philosophers_action_2(t_desk *desk, int phil_idx);

/***********************/
/*****   action.c  *****/
/***********************/
//int				eating(t_philosopher *phil);
//int				thinking(t_philosopher *phil);
//int				sleeping(t_philosopher *phil);
int				eating(t_desk *desk, int phil_idx);
int				thinking(t_desk *desk, int phil_idx);
int				sleeping(t_desk *desk, int phil_idx);
int 			check_die(t_desk *desk, int phil_idx);
#endif
