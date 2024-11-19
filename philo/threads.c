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
	pthread_mutex_lock(&sim->mutex_print);
	if (sim->loop == 0)
		printf("%li %i is thinking\n", set_time() - sim->start_time, philo->n_philo); //add +1
	pthread_mutex_unlock(&sim->mutex_print);
}

int	to_eat(t_philos *philo, t_simulation *sim)
{
	if (one_philo_sim(philo, sim) == 1)
		return (1);

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
	//eating
	if (eating(philo, sim) == 1)
		return (1);
	//leave forks
	//printf("%li philo %i left forks, last_eat: %li\n", set_time() - philo->sim->start_time, philo->n_philo, (philo->last_eat - sim->start_time)); //borrar
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (0);
}

int	to_sleep(t_philos *philo)
{
	philo->act_time = set_time();
	if (philo->act_time - philo->last_eat > philo->p_to_die)
	{
		pthread_mutex_lock(&philo->sim->mutex_print);
		if (philo->sim->loop == 0)
			printf("%li %i died (sleep 1)\n", philo->act_time, philo->n_philo);
		philo->p_to_die = 0;
		pthread_mutex_unlock(&philo->sim->mutex_print);
		return (1);
	}
	if (philo->p_to_sleep > philo->p_to_die)
	{
		pthread_mutex_lock(&philo->sim->mutex_print);
		if (philo->sim->loop == 0)
			printf("%li %i died (sleep 2)\n", philo->act_time, philo->n_philo);
		pthread_mutex_unlock(&philo->sim->mutex_print);
		sleeping(philo, philo->p_to_die, philo->sim);
		pthread_mutex_lock(&philo->sim->mutex_print);
		philo->p_to_die = 0;
		pthread_mutex_unlock(&philo->sim->mutex_print);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->sim->mutex_print);
		if (philo->sim->loop == 0)
			printf("%li %i is sleeping\n", set_time() - philo->sim->start_time, philo->n_philo); //add +1
		pthread_mutex_unlock(&philo->sim->mutex_print);
		sleeping(philo, philo->p_to_sleep, philo->sim);
	}
	return (0);
}

void	*do_smth(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	printf("hola hilo %i\n", philo->n_philo);//borrar
	if (philo->n_philo % 2 != 0)
	{
		if (philo->p_to_eat > philo->p_to_die)
			sleeping(philo, philo->p_to_die, philo->sim);
		else
			sleeping(philo, philo->p_to_eat - 10, philo->sim);
	}
	//t_to_die t_to_eat t_to_sleep
	while (1)
	{
		if (to_eat(philo, philo->sim) == 1)
		{
			pthread_mutex_lock(&philo->sim->mutex_print);
			if (philo->sim->loop == 0)
				printf("%li %i died (eat 0)\n", set_time() - philo->sim->start_time, philo->n_philo);
			pthread_mutex_unlock(&philo->sim->mutex_print);
			break;
		}
		if (to_sleep(philo) == 1)
		{
			pthread_mutex_lock(&philo->sim->mutex_print);
			if (philo->sim->loop == 0)
				printf("%li %i died (sleep 0)\n", set_time() - philo->sim->start_time, philo->n_philo);
			pthread_mutex_unlock(&philo->sim->mutex_print);
			break;
		}
		to_think(philo, philo->sim);
		if ((philo->sim->t_must_eat <= 0 && philo->p_must_eat > 0) || philo->sim->loop == 1)
		{
			philo->p_to_die = 0;
			break ;
		}
	}
	printf("out loop\n");//borrar
	return (NULL);
}

void	*death(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	printf("im death %li\n", sim->n_philos);
	while (sim->loop == 0)
	{
		i = 0;
		while (i < sim->n_philos)
		{
			if (sim->philos[i].p_to_die == 0)
			{
				pthread_mutex_lock(&sim->mutex_print);
				sim->loop = 1;
				printf("outing\n");
				pthread_mutex_unlock(&sim->mutex_print);
				break ;
			}
			i++;
		}
	}
	printf("outed\n");
	return (NULL);
}

//comer->dormir->pensar
int	create_threads(t_simulation *sim)
{
	int				created;
	int				i;

	pthread_mutex_init(&sim->mutex, NULL);
	pthread_mutex_init(&sim->mutex_print, NULL);
	sim->t_must_eat = (sim->n_philos * sim->t_must_eat);

	printf("times_to_eat: %li\n", sim->t_must_eat);//borrar
	printf("n_philos= %li\n", sim->n_philos); //borrar
	pthread_create(&(sim->death_thread), NULL, death, sim);
	sim->start_time = set_time();
	i = 0;
	while (i < sim->n_philos)
	{
		sim->philos[i].last_eat = set_time();
		created = pthread_create(&(sim->philos[i].thread_id), NULL, do_smth, &sim->philos[i]);
		if (created != 0)
			return (1);
		printf("created philo %i\n", sim->philos[i].n_philo); //borrar
		i++;
	}

	i = 0;
	while (i < sim->n_philos)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(sim->death_thread, NULL);
	printf("times_to_eat: %li\n", sim->t_must_eat);//borrar

	i = 0;
	while (i < sim->n_philos)
	{
		pthread_mutex_destroy(&sim->philos->right_fork);
		i++;
	}
	pthread_mutex_destroy(&sim->mutex);
	printf("total time = %li\n", set_time() - sim->start_time);//borrar
	return (0);
}

/*
1 800 200 200 (muere)
5 800 200 200 (viven)
5 800 200 200 7 (viven y cada uno come 7 veces)
4 410 200 200 (viven)
4 310 200 100 (mueren)
3 310 103 103 (tienen que vivir)
3 310 104 104 (tienen que morir)
181 400 200 200 (mueren)
*/