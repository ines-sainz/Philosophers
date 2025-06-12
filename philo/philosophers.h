/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:41:17 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/15 09:41:22 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//gettimeofday
# include <sys/time.h>

//pthread_create pthread_detach pthread_join pthread_mutex_init
//pthread_mutex_destroy pthread_mutex_lock pthread_mutex_unlock
# include <pthread.h>

//write usleep
# include <unistd.h>

//printf
# include <stdio.h>

//malloc free
# include <stdlib.h>

//memset
# include <string.h>

//INT_MAX INT_MIN
# include <stdint.h>
# include <limits.h>

typedef struct s_philos
{
	struct s_simulation	*sim;
	int					n_philo;
	pthread_t			thread_id;
	int					p_to_die;
	int					p_to_eat;
	int					p_to_sleep;
	int					p_must_eat;
	long				last_eat;
	long				act_time;
	long				philo_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		right_fork;
}						t_philos;

typedef struct s_simulation
{
	pthread_t		death_thread;
	long			n_philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_print;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			t_must_eat;
	long			start_time;
	t_philos		*philos;
	int				loop;
}					t_simulation;

int			parse(char **argv, t_simulation *sim);
int			set_philos(t_simulation *sim);
int			create_threads(t_simulation *sim);
long		set_time(void);
int			sleeping(t_philos *philo, long time_to_sleep, t_simulation *sim);
int			one_philo_sim(t_philos *philo, t_simulation *sim);
int			eating(t_philos *philo, t_simulation *sim);
void		print_actions(t_simulation *sim, t_philos *philo, char *action);
void		*death(void *arg);
int			to_eat(t_philos *philo, t_simulation *sim);

// LIBFT
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
