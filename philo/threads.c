/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:16:14 by isainz-r          #+#    #+#             */
/*   Updated: 2024/11/04 17:16:15 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	to_think(t_philos *philo, t_simulation *sim)
{
	print_actions(sim, philo, "is thinking");
	if (philo->n_philo % 2 != 0 && (sim->n_philos % 2 != 0))
		sleeping(philo, 1, sim);
}

int	to_sleep(t_philos *philo)
{
	philo->act_time = set_time();
	if (philo->act_time - philo->last_eat > philo->p_to_die)
	{
		print_actions(philo->sim, philo, "died");
		return (1);
	}
	if (philo->p_to_sleep > philo->p_to_die)
	{
		sleeping(philo, philo->p_to_die, philo->sim);
		print_actions(philo->sim, philo, "died");
		return (1);
	}
	else
	{
		print_actions(philo->sim, philo, "is sleeping");
		sleeping(philo, philo->p_to_sleep, philo->sim);
	}
	return (0);
}

void	*do_smth(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->n_philo % 2 == 0)
		usleep(500);
	while (1)
	{
		if (to_eat(philo, philo->sim) == 1)
			break ;
		if (to_sleep(philo) == 1)
			break ;
		to_think(philo, philo->sim);
		pthread_mutex_lock(&philo->sim->mutex_print);
		if (philo->sim->loop == 1)
		{
			pthread_mutex_unlock(&philo->sim->mutex_print);
			philo->p_to_die = 0;
			break ;
		}
		else
			pthread_mutex_unlock(&philo->sim->mutex_print);
	}
	return (NULL);
}

void	destroy_threads_and_mutex(t_simulation *sim)
{
	int	i;

	pthread_join(sim->death_thread, NULL);
	i = 0;
	while (i < sim->n_philos)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < sim->n_philos)
	{
		pthread_mutex_destroy(&sim->philos->right_fork);
		i++;
	}
	pthread_mutex_destroy(&sim->mutex);
}

int	create_threads(t_simulation *sim)
{
	int				created;
	int				i;

	pthread_mutex_init(&sim->mutex, NULL);
	pthread_mutex_init(&sim->mutex_print, NULL);
	sim->t_must_eat = (sim->n_philos * sim->t_must_eat);
	sim->start_time = set_time();
	i = 0;
	while (i < sim->n_philos)
	{
		sim->philos[i].last_eat = set_time();
		created = pthread_create(&(sim->philos[i].thread_id),
				NULL, do_smth, &sim->philos[i]);
		if (created != 0)
			return (1);
		i++;
	}
	pthread_create(&(sim->death_thread), NULL, death, sim);
	destroy_threads_and_mutex(sim);
	return (0);
}

/*
1 800 200 200 (muere)
5 800 200 200 (viven)
5 800 200 200 7 (viven y cada uno come 7 veces)
4 410 200 200 (viven)
4 410 200 200 10 (viven y cada uno come 10 veces)
4 310 200 100 (mueren)
4 200 205 200 (muere)
3 310 103 103 (tienen que vivir)
3 310 104 104 (tienen que morir)
181 400 200 200 (mueren)
50 800 200 200 (viven)
100 800 200 200 (viven)
105 800 200 200 (viven)
200 800 200 200 (viven)
5 600 150 150 (viven)

-5 600 200 200 (error)
4 -5 200 200 (error)
4 600 -5 200 (error)
4 600 200 -5 (error)
4 600 200 200 -5 (error)
*/