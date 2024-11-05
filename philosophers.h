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

# include <stdint.h>
//gettimeofday
# include <sys/time.h>
//pthread_create pthread_detach pthread_join
# include <pthread.h>
//write usleep
# include <unistd.h>
//printf
# include <stdio.h>
//malloc free
# include <stdlib.h>
//memset
# include <string.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_philos
{
	int				n_philo;
	pthread_t		thread_id;
	int				p_to_die;
	int				p_to_eat;
	int				p_to_sleep;
	int				p_must_eat;
	int				left_fork;
	int				right_fork;
	struct s_philos	*next;
}					t_philos;

typedef struct s_forks
{
	int				n_fork;
	int				used;
	struct s_forks	*next;
}					t_forks;

typedef struct s_simulation
{
	int		test;
	long		n_philos;
	pthread_mutex_t	mutex; //inicializarlo de manera global
	long		t_to_die;
	long		t_to_eat;
	long		t_to_sleep;
	long		t_must_eat;
	t_philos	*first_philo;
	t_philos	*p_iterator;
	t_forks		*first_fork;
	t_forks		*f_iterator;
}				t_simulation;

int			parse(char **argv, t_simulation *sim);
int			set_philos(t_simulation *sim);
void		clear_philos(t_simulation *sim);
void		add_back_philo(t_philos *philo, t_simulation *sim);
t_philos	*new_philo(int i, t_simulation *sim);
void		print_philos(t_simulation *sim);
int			set_forks(t_simulation *sim);
void		clear_forks(t_simulation *sim);
void		add_back_fork(t_forks *fork, t_simulation *sim);
t_forks		*new_fork(int i);
void		print_forks(t_simulation *sim);
int			create_threads(t_simulation sim);

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
