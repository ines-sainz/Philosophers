/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:36:51 by isainz-r          #+#    #+#             */
/*   Updated: 2024/11/21 14:36:52 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Checks if a philosopher has died or met eating requirements.
 *
 * Compares the philosopher's last meal time with the allowed time to die.
 * If the philosopher has died, sets flags and prints a message. Also checks
 * if all meals have been completed based on simulation parameters.
 *
 * @param sim Pointer to the simulation structure.
 * @param last_eat Last time the philosopher ate (will be updated inside).
 * @param i Index of the philosopher in the simulation array.
 * @return 1 if the philosopher has died or the simulation should stop,
 *         0 otherwise.
 */
int	ask_death(t_simulation *sim, long last_eat, int i)
{
	pthread_mutex_lock(&sim->mutex);
	last_eat = sim->philos[i].last_eat;
	if ((set_time() - last_eat) > sim->t_to_die)
	{
		print_actions(sim, &sim->philos[i], "died");
		sim->philos[i].p_to_die = 0;
	}
	pthread_mutex_unlock(&sim->mutex);
	pthread_mutex_lock(&sim->mutex_print);
	if (sim->philos[i].p_to_die == 0)
	{
		sim->loop = 1;
		printf("%li %i died\n", set_time() - sim->start_time,
			sim->philos[i].n_philo);
		pthread_mutex_unlock(&sim->mutex_print);
		return (1);
	}
	else if (sim->t_must_eat <= 0 && sim->philos[i].p_must_eat > 0)
	{
		sim->loop = 1;
		pthread_mutex_unlock(&sim->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(&sim->mutex_print);
	return (0);
}

/**
 * @brief Thread function to monitor philosopher deaths.
 *
 * Continuously loops through all philosophers, checking if any have died
 * using ask_death(). Exits the loop and returns when a death is detected
 * or the simulation ends.
 *
 * @param arg Pointer to the simulation structure, cast as void*.
 * @return NULL when the monitoring thread ends.
 */
void	*death(void *arg)
{
	t_simulation	*sim;
	int				i;
	long			last_eat;

	last_eat = 0;
	sim = (t_simulation *)arg;
	while (sim->loop == 0)
	{
		i = 0;
		while (i < sim->n_philos)
		{
			if (ask_death(sim, last_eat, i) == 1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
