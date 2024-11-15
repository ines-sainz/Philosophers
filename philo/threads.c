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

void	to_think(t_philos *philos, t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex_print);
	printf("%li %i is thinking\n", set_time() - sim->start_time, philos->n_philo); //add +1
	pthread_mutex_unlock(&sim->mutex_print);
}

int	to_eat(t_philos *philo, t_simulation *sim)
{
	long	act_time;

	if (sim->n_philos == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&sim->mutex_print);
		printf("%li %i has taken the right fork\n", set_time() - sim->start_time, philo->n_philo); //-right ++1
		sleeping(sim->t_to_die, sim);
		pthread_mutex_unlock(&philo->right_fork);
		printf("%li %i died before eating\n", set_time() - sim->start_time, philo->n_philo); //-where ++1
		pthread_mutex_unlock(&sim->mutex_print);
		sim->loop = 1;
		return (1);
	}
	//lock right fork
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&sim->mutex_print);
	printf("%li %i has taken the right fork\n", set_time() - sim->start_time, philo->n_philo); //-right ++1
	pthread_mutex_unlock(&sim->mutex_print);

	//lock left fork
	pthread_mutex_lock(&(*philo->left_fork));
	pthread_mutex_lock(&sim->mutex_print);
	printf("%li %i has taken the left fork\n", set_time() - sim->start_time, philo->n_philo); //-left ++1
	pthread_mutex_unlock(&sim->mutex_print);

	//eating
	pthread_mutex_lock(&sim->mutex_print);
	act_time = set_time();
	printf("act_time - last_eat: %li to_eat: %li to_die: %li last_eat: %li\n",
		(act_time - philo->last_eat), sim->t_to_eat, sim->t_to_die, (philo->last_eat - sim->start_time));
	sim->t_must_eat--;
	if (act_time - philo->last_eat > sim->t_to_die)
	{
		printf("%li %i has died before eating\n", set_time() - sim->start_time, philo->n_philo); //-where ++1
		sim->loop = 1;
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&sim->mutex_print);
		return (1);
	}
	philo->last_eat = act_time;
	pthread_mutex_unlock(&sim->mutex_print);
	if (sim->t_to_eat > sim->t_to_die)
	{
		printf("%li %i has died while eating\n", act_time - sim->start_time, philo->n_philo); //-where ++1
		sleeping(sim->t_to_die, sim);
		sim->loop = 1;
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf("%li %i is eating\n", act_time - sim->start_time, philo->n_philo); //add +1
	sleeping(sim->t_to_eat, sim);

	//leave forks
	printf("%li philo %i left forks, last_eat: %li\n", set_time() - philo->sim->start_time, philo->n_philo, (philo->last_eat - sim->start_time));
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	to_sleep(t_philos *philo)
{
	long	act_time;

	pthread_mutex_lock(&philo->sim->mutex_print);
	act_time = set_time();
	if (act_time - philo->last_eat > philo->p_to_die)
	{
		printf("philo %i died before sleeping\n", philo->n_philo);
		pthread_mutex_unlock(&philo->sim->mutex_print);
		philo->sim->loop = 1;
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->mutex_print);
	if (philo->p_to_sleep > philo->p_to_die)
	{
		printf("philo %i died while sleeping\n", philo->n_philo);
		sleeping(philo->p_to_die, philo->sim);
		philo->sim->loop = 1;
		return (1);
	}
	else
		sleeping(philo->p_to_sleep, philo->sim);
	return (0);
}

void	*do_smth(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	printf("hola hilo %i\n", philo->sim->test);
	if (philo->n_philo % 2 != 0)
	{
		if (philo->p_to_eat > philo->p_to_die)
			sleeping(philo->p_to_die, philo->sim);
		else
			sleeping(philo->p_to_eat, philo->sim);
	}
	//t_to_die t_to_eat t_to_sleep
	while (1)
	{
		if (to_eat(philo, philo->sim) == 1)
		{
			pthread_mutex_lock(&philo->sim->mutex_print);
			printf("%li philo %i has died in eating\n", set_time() - philo->sim->start_time, philo->n_philo);
			pthread_mutex_unlock(&philo->sim->mutex_print);
			break;
		}
		if (to_sleep(philo) == 1)
		{
			pthread_mutex_lock(&philo->sim->mutex_print);
			printf("%li philo %i has died in sleeping\n", set_time() - philo->sim->start_time, philo->n_philo);
			pthread_mutex_unlock(&philo->sim->mutex_print);
			break;
		}
		to_think(philo, philo->sim);
		if ((philo->sim->t_must_eat <= 0 && philo->p_must_eat > 0) || philo->sim->loop == 1)
			break ;
	}
	printf("out loop\n");
	return (NULL);
}

//comer->dormir->pensar
int	create_threads(t_simulation *sim)
{
	int				created;
	int				i;

	(void)sim;

	printf ("start time %li\n", sim->start_time);

	pthread_mutex_init(&sim->mutex, NULL);
	pthread_mutex_init(&sim->mutex_print, NULL);

	sim->t_must_eat = (sim->n_philos * sim->t_must_eat) - 1;
	if (sim->t_must_eat == 0)
		sim->t_must_eat = -1;
	printf("times_to_eat: %li\n", sim->t_must_eat);

	printf("n_philos= %li\n", sim->n_philos);
	sim->start_time = set_time();
	i = 0;
	while (i < sim->n_philos)
	{
		sim->philos[i].last_eat = sim->start_time;
		created = pthread_create(&(sim->philos[i].thread_id), NULL, do_smth, &sim->philos[i]);
		if (created != 0)
			return (1);
		printf("created philo %i\n", sim->philos[i].n_philo);
		i++;
	}

	i = 0;
	while (i < sim->n_philos)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}

	printf("times_to_eat: %li\n", sim->t_must_eat);

	i = 0;
	while (i < sim->n_philos)
	{
		pthread_mutex_destroy(&sim->philos->right_fork);
		i++;
	}
	pthread_mutex_destroy(&sim->mutex);
	printf("end time %li\n", set_time());
	printf("total time = %li\n", set_time() - sim->start_time);
	return (0);
}
