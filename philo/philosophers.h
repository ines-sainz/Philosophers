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
	int				n_philo;
	pthread_t		thread_id;
	int				p_to_die;
	int				p_to_eat;
	int				p_to_sleep;
	int				p_must_eat;
	long			last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philos;

/*typedef struct s_forks
{
	int				n_fork;
	int				used;
	pthread_mutex_t	fork_mutxex;
}					t_forks;*/

typedef struct s_simulation
{
	int		test;
	long			n_philos;
	pthread_mutex_t	mutex; //inicializarlo de manera global
	pthread_mutex_t	mutex_print;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			t_must_eat;
	long			start_time;
	t_philos		*philos;
	//t_forks			*forks;
}					t_simulation;

int			parse(char **argv, t_simulation *sim);
int			set_philos(t_simulation *sim);
void		print_philos(t_simulation *sim);
int			set_forks(t_simulation *sim);
void		print_forks(t_simulation *sim);
int			create_threads(t_simulation *sim);//, t_philos first_philo);
long		set_time(void);

//LIBFT
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isdigit(int c);

#endif

/*
NEW FUNCTIONS
-   int usleep(useconds_t usec);
-   int pthread_join(pthread_t thread, void **retval);
-   int pthread_create(pthread_t *restrict thread,
        const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
-   int pthread_detach(pthread_t thread);
-   int gettimeofday(struct timeval *restrict tv, struct timezone *_Nullable restrict tz);
*/
