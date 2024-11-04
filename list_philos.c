/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:06:28 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/31 09:06:31 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_forks(t_simulation *sim)
{
	sim->f_iterator = sim->first_fork;
	printf("FORK\n");
	while (sim->f_iterator != NULL)
	{
		printf("nº fork: %i   used: %i\n", sim->f_iterator->n_fork, sim->f_iterator->used);
		sim->f_iterator = sim->f_iterator->next;
	}
	printf("...\n");
}

void	clear_philos(t_simulation *sim)
{
	t_philos	*philo;

	while (sim->first_philo != NULL)
	{
		philo = sim->first_philo;
		sim->first_philo = sim->first_philo->next;
		free(philo);
	}
	sim->first_philo = NULL;
}

void	add_back_philo(t_philos *philo, t_simulation *sim)
{
	if (sim->first_philo == NULL)
	{
		sim->first_philo = philo;
		return ;
	}
	sim->p_iterator = sim->first_philo;
	while (sim->p_iterator->next != NULL)
		sim->p_iterator = sim->p_iterator->next;
	sim->p_iterator->next = philo;
}

t_philos	*new_philo(int i, t_simulation *sim)
{
	t_philos	*philo;

	philo = (t_philos *)malloc(sizeof(t_philos));
	if (!philo)
		return (0);
	philo->n_philo = i;
	philo->p_to_die = sim->t_to_die;
	philo->p_to_eat = sim->t_to_eat;
	philo->p_to_sleep = sim->t_to_sleep;
	philo->p_must_eat = sim->t_must_eat;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->next = NULL;
	return (philo);
}
