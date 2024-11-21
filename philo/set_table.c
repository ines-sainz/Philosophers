/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:20:26 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/31 10:20:29 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philos *philo, long time_to_sleep, t_simulation *sim)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->act_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	philo->philo_time = 0;
	pthread_mutex_lock(&philo->sim->mutex_print);
	while (philo->philo_time < time_to_sleep
		&& (philo->philo_time < sim->t_to_die || sim->loop == 0))
	{
		pthread_mutex_unlock(&philo->sim->mutex_print);
		gettimeofday(&time, NULL);
		philo->philo_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		philo->philo_time -= philo->act_time;
		pthread_mutex_lock(&philo->sim->mutex_print);
	}
	pthread_mutex_unlock(&philo->sim->mutex_print);
	return (0);
}

long	set_time(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

int	set_philos(t_simulation *sim)
{
	int			i;

	sim->philos = (t_philos *)malloc(sim->n_philos * sizeof(t_philos));
	if (!sim->philos)
		return (1);
	i = 0;
	while (i < sim->n_philos)
	{
		sim->philos[i].sim = sim;
		sim->philos[i].n_philo = i + 1;
		sim->philos[i].p_to_die = sim->t_to_die;
		sim->philos[i].p_to_eat = sim->t_to_eat;
		sim->philos[i].p_to_sleep = sim->t_to_sleep;
		sim->philos[i].p_must_eat = sim->t_must_eat;
		pthread_mutex_init(&sim->philos[i].right_fork, NULL);
		if (i != 0)
			sim->philos[i].left_fork = &sim->philos[i - 1].right_fork;
		i++;
	}
	sim->philos[0].left_fork = &sim->philos[sim->n_philos - 1].right_fork;
	return (0);
}
