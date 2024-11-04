/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:01:42 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/30 12:01:44 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philos(t_simulation *sim)
{
	sim->p_iterator = sim->first_philo;
	while (sim->p_iterator != NULL)
	{
		printf("nº philo: %i\nleft fork: %i\nright fork: %i\n...\n",
			sim->p_iterator->n_philo, sim->p_iterator->left_fork, sim->p_iterator->right_fork);
		sim->p_iterator = sim->p_iterator->next;
	}
}

void	clear_forks(t_simulation *sim)
{
	t_forks	*fork;

	while (sim->first_fork != NULL)
	{
		fork = sim->first_fork;
		sim->first_fork = sim->first_fork->next;
		free(fork);
	}
	sim->first_fork = NULL;
}

void	add_back_fork(t_forks *fork, t_simulation *sim)
{
	if (sim->first_fork == NULL)
	{
		sim->first_fork = fork;
		return ;
	}
	sim->f_iterator = sim->first_fork;
	while (sim->f_iterator->next != NULL)
		sim->f_iterator = sim->f_iterator->next;
	sim->f_iterator->next = fork;
}

t_forks	*new_fork(int i)
{
	t_forks	*fork;

	fork = (t_forks *)malloc(sizeof(t_forks));
	if (!fork)
		return (0);
	fork->n_fork = i;
	fork->used = 0;
	fork->next = NULL;
	return (fork);
}
