/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 23:11:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/29 22:24:14 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>

# define THREAD_LIMIT 100

struct timeval	g_start_time;

pthread_mutex_t	g_lock;
pthread_mutex_t	g_lock_write;
pthread_mutex_t	g_lock2;
pthread_mutex_t	g_write_kill;

typedef enum s_state
{
	scratch_balls,
	eating,
	sleeping,
	thinking,
	is_dead
}	t_state;

typedef struct s_info
{
	int			id;
	pthread_t	t;
	long		time;
	bool		*fork_left;
	bool		*fork_rigth;
	t_state		st;
	long		started_eating;
	int			c_eat;
	pthread_mutex_t	*left_fork_m;
	pthread_mutex_t	*rigth_fork_m;
}	t_info;

typedef struct s_args
{
	int	total_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	how_many_times_to_eat;
	int	time_to_eat;
	int	nbr_philo;
}	t_args;

typedef struct s_philo
{
	t_info			*philo;
	bool			*forks;
	int				nmr_p;
	pthread_mutex_t	*forks_m;
}	t_philo;

t_args			g_args;

void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
long	stop_eating(t_info *p);
void	init_philo(t_philo *p);
void	init_args(int ac, char **av);
long	calculate_time(long time);
long	get_time(void);
void	give_forks(t_info *p, long time_passed);
long	check_death_while_sleeping(t_info *p, long time_passed);
long	check_death_while_eating(t_info *p);
long	check_death(long time_passed, t_info *p);

#endif
