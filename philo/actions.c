/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:10:32 by isainz-r          #+#    #+#             */
/*   Updated: 2024/11/15 10:10:36 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_philos *philo, t_simulation *sim)
{
	philo->act_time = set_time();
	sim->t_must_eat--;
	if (philo->act_time - philo->last_eat > sim->t_to_die)
	{
		pthread_mutex_lock(&sim->mutex_print);
		if (sim->loop == 0)
			printf("%li %i died (eat 1)\n", philo->act_time - sim->start_time, philo->n_philo); //-where ++1
		sim->loop = 1;
		pthread_mutex_unlock(&sim->mutex_print);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	philo->last_eat = philo->act_time;
	if (sim->t_to_eat > sim->t_to_die)
	{
		sleeping(philo, sim->t_to_die, sim);
		pthread_mutex_lock(&sim->mutex_print);
		if (sim->loop == 0)
			printf("%li %i died (eat 2)\n", set_time() - sim->start_time, philo->n_philo); //-where ++1
		sim->loop = 1;
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&sim->mutex_print);
	if (sim->loop == 0)
		printf("%li %i is eating\n", philo->act_time - sim->start_time, philo->n_philo); //add +1
	pthread_mutex_unlock(&sim->mutex_print);
	sleeping(philo, sim->t_to_eat, sim);
	return (0);
}

void	lock_forks(t_philos *philo, t_simulation *sim)
{
	//lock right fork
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&sim->mutex_print);
	if (sim->loop == 0)
		printf("%li %i has taken a fork (right)\n", set_time() - sim->start_time, philo->n_philo); //-right ++1
	pthread_mutex_unlock(&sim->mutex_print);

	//lock left fork
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&sim->mutex_print);
	if (sim->loop == 0)
		printf("%li %i has taken a fork (left)\n", set_time() - sim->start_time, philo->n_philo); //-left ++1
	pthread_mutex_unlock(&sim->mutex_print);

}

int	one_philo_sim(t_philos *philo, t_simulation *sim)
{
	if (sim->n_philos == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&sim->mutex_print);
		printf("%li %i has taken a fork (right)\n", set_time() - sim->start_time, philo->n_philo); //-right ++1
		sleeping(philo, sim->t_to_die, sim);
		pthread_mutex_unlock(&philo->right_fork);
		printf("%li %i died (eat 3)\n", set_time() - sim->start_time, philo->n_philo); //-where ++1
		sim->loop = 1;
		pthread_mutex_unlock(&sim->mutex_print);
		return (1);
	}
	return (0);
}
