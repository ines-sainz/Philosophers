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

	sim->forks = (t_forks *)malloc(sim->n_philos * sizeof(t_forks));
	if (!sim->forks)
	{
		free(sim->philos);
		return (1);
	}
	i = 0;
	while (i < sim->n_philos)
	{
		sim->forks[i].n_fork = i;
		sim->forks[i].used = 0;
		i++;
	}
	return (0);
}

void	print_forks(t_simulation *sim)
{
	int		i;

	i = 0;
	while (i < sim->n_philos)
	{
		printf("nºfork: %i   used: %i\n", sim->forks[i].n_fork, sim->forks[i].used);
		i++;
	}
	printf("...\n");
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
		sim->philos[i].n_philo = i;
		sim->philos[i].p_to_die = sim->t_to_die;
		sim->philos[i].p_to_eat = sim->t_to_eat;
		sim->philos[i].p_to_sleep = sim->t_to_sleep;
		sim->philos[i].p_must_eat = sim->t_must_eat;
		sim->philos[i].left_fork = 0;
		sim->philos[i].right_fork = 0;
		i++;
	}
	return (0);
}

void	print_philos(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_philos)
	{
		printf("nº philo: %i   p_to_die: %i   p_to_eat: %i   p_to_sleep: %i   p_must_eat:%i   left fork: %i   right fork: %i\n",
		sim->philos[i].n_philo, sim->philos[i].p_to_die, sim->philos[i].p_to_eat,
		sim->philos[i].p_to_sleep, sim->philos[i].p_must_eat,
		sim->philos[i].left_fork, sim->philos[i].right_fork);
		i++;
	}
	printf("...\n");
}
