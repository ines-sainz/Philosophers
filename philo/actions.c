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

/**
 * @brief Executes the eating action for a philosopher and checks for death.
 *
 * Updates the philosopher's last eating time, prints actions, and simulates
 * eating while checking if the philosopher has died due to starvation.
 *
 * @param philo Pointer to the philosopher structure.
 * @param sim Pointer to the simulation structure.
 * @return 1 if the philosopher dies during the action, 0 otherwise.
 */
int	eating(t_philos *philo, t_simulation *sim)
{
	philo->act_time = set_time();
	if (philo->act_time - philo->last_eat > sim->t_to_die)
	{
		print_actions(sim, philo, "died");
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (sim->t_to_eat > sim->t_to_die)
	{
		print_actions(sim, philo, "is eating");
		sleeping(philo, sim->t_to_die, sim);
		print_actions(sim, philo, "died");
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&sim->mutex);
	philo->last_eat = set_time();
	pthread_mutex_unlock(&sim->mutex);
	print_actions(sim, philo, "is eating");
	sleeping(philo, sim->t_to_eat, sim);
	return (0);
}

/**
 * @brief Handles the process for a philosopher to eat.
 *
 * Manages the acquisition of forks (mutexes), invokes the eating routine,
 * and releases the forks afterwards. Handles odd and even philosopher
 * ordering for avoiding deadlocks.
 *
 * @param philo Pointer to the philosopher structure.
 * @param sim Pointer to the simulation structure.
 * @return 1 if the philosopher dies during the process, 0 otherwise.
 */
int	to_eat(t_philos *philo, t_simulation *sim)
{
	if (one_philo_sim(philo, sim) == 1)
		return (1);
	if (philo->n_philo % 2 != 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_actions(sim, philo, "has taken a fork");
	}
	pthread_mutex_lock(philo->left_fork);
	print_actions(sim, philo, "has taken a fork");
	if (philo->n_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_actions(sim, philo, "has taken a fork");
	}
	if (eating(philo, sim) == 1)
		return (1);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

/**
 * @brief Handles the edge case where there is only one philosopher.
 *
 * Since the philosopher cannot acquire two forks, simulates their death after
 * the time to die expires.
 *
 * @param philo Pointer to the philosopher structure.
 * @param sim Pointer to the simulation structure.
 * @return 1 if it's a one-philosopher simulation (and it ends), 0 otherwise.
 */
int	one_philo_sim(t_philos *philo, t_simulation *sim)
{
	if (sim->n_philos == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&sim->mutex_print);
		printf("%li %i has taken a fork\n", set_time() - sim->start_time,
			philo->n_philo);
		pthread_mutex_unlock(&sim->mutex_print);
		usleep(sim->t_to_die * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&sim->mutex_print);
		philo->p_to_die = 0;
		pthread_mutex_unlock(&sim->mutex_print);
		return (1);
	}
	return (0);
}

/**
 * @brief Prints the current action of a philosopher if the simulation is active.
 *
 * Ensures synchronized printing using a mutex. Handles the special case of
 * printing a death message and updates the simulation state accordingly.
 *
 * @param sim Pointer to the simulation structure.
 * @param philo Pointer to the philosopher structure.
 * @param action String describing the action to print.
 */
void	print_actions(t_simulation *sim, t_philos *philo, char *action)
{
	static int	print_death;

	if (ft_strncmp(action, "died", 4) == 0)
	{
		pthread_mutex_lock(&philo->sim->mutex_print);
		if (sim->loop == 0 && (print_death && print_death == 0))
		{
			print_death = 1;
			printf("%li %i died\n", set_time() - sim->start_time,
				philo->n_philo);
			philo->p_to_die = 0;
		}
		pthread_mutex_unlock(&philo->sim->mutex_print);
		return ;
	}
	pthread_mutex_lock(&sim->mutex_print);
	if (!print_death)
		print_death = 0;
	if (sim->loop == 0 && print_death == 0)
		printf("%li %i %s\n", set_time() - sim->start_time,
			philo->n_philo, action);
	if (ft_strncmp(action, "is eating", 4) == 0)
		sim->t_must_eat--;
	pthread_mutex_unlock(&sim->mutex_print);
}
