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

int	set_forks(t_simulation *sim)
{
	int		i;
	t_forks	*fork;

	i = 1;
	while (i <= sim->n_philos)
	{
		fork = new_fork(i);
		if (!fork)
		{
			clear_forks(sim);
			return (1);
		}
		add_back_fork(fork, sim);
		i++;
	}
	return (0);
}

int	set_philos(t_simulation *sim)
{
	int			i;
	t_philos	*philo;

	i = 1;
	while (i <= sim->n_philos)
	{
		philo = new_philo(i, sim);
		if (!philo)
		{
			clear_philos(sim);
			return (1);
		}
		add_back_philo(philo, sim);
		i++;
	}
	return (0);
}
