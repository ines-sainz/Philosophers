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
