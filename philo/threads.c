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
	printf("%li im philo %i and im thinking\n", set_time() - sim->start_time, philos->n_philo);
	//printf("%li set time\n", set_time());
	pthread_mutex_unlock(&sim->mutex_print);
	/*pthread_mutex_lock(&sim->mutex);
	sim->test--;
	pthread_mutex_unlock(&sim->mutex);*/
}

int	to_eat(t_philos *philo, t_simulation *sim)
{
	long	act_time;

	if (sim->n_philos == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&sim->mutex_print);
		printf("%li im philo %i and i took the right fork\n", set_time() - sim->start_time, philo->n_philo);
		sleeping(sim->t_to_die, sim);
		//usleep(sim->t_to_die * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		printf("%li philo %i died before eating\n", set_time() - sim->start_time, philo->n_philo);
		pthread_mutex_unlock(&sim->mutex_print);
		sim->loop = 1;
		return (1);
	}
	//lock right fork
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&sim->mutex_print);
	printf("%li im philo %i and i took the right fork\n", set_time() - sim->start_time, philo->n_philo);
	pthread_mutex_unlock(&sim->mutex_print);

	//lock left fork
	pthread_mutex_lock(&(*philo->left_fork));
	pthread_mutex_lock(&sim->mutex_print);
	printf("%li im philo %i and i took the left fork\n", set_time() - sim->start_time, philo->n_philo);
	pthread_mutex_unlock(&sim->mutex_print);

	//eating
	pthread_mutex_lock(&sim->mutex_print);
	act_time = set_time();
	printf("act_time - last_eat: %li to_eat: %li to_die: %li last_eat: %li\n",
		(act_time - philo->last_eat), sim->t_to_eat, sim->t_to_die, (philo->last_eat - sim->start_time));
	sim->t_must_eat--;
	if (act_time - philo->last_eat > sim->t_to_die)
	{
		printf("philo %i died before eating\n", philo->n_philo);
		sim->loop = 1;
		return (1);
	}
	philo->last_eat = act_time;
	pthread_mutex_unlock(&sim->mutex_print);
	if (sim->t_to_eat > sim->t_to_die)
	{
		printf("philo %i died while eating\n", philo->n_philo);
		sleeping(sim->t_to_die, sim);
		//usleep(sim->t_to_die * 1000);
		sim->loop = 1;
		return (1);
	}
	printf("%li im philo %i and im eating\n", act_time - sim->start_time, philo->n_philo);
	sleeping(sim->t_to_eat, sim);
	//usleep(sim->t_to_eat * 1000);

	//leave forks
	printf("%li philo %i left forks, last_eat: %li\n", set_time() - philo->sim->start_time, philo->n_philo, (philo->last_eat - sim->start_time));
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

	return (0);

/*
	pthread_mutex_lock(&sim->mutex_print);
	sim->t_must_eat--;
	printf("%li im philo %i and im eating\n", set_time() - sim->start_time, philos->n_philo);
	pthread_mutex_unlock(&sim->mutex_print);*/
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
		//usleep(philo->p_to_die * 1000);
		philo->sim->loop = 1;
		return (1);
	}
	else
	{
		sleeping(philo->p_to_sleep, philo->sim);
		//usleep(philo->p_to_sleep * 1000);
	}
	return (0);
}

void	*do_smth(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	/*int i = 0;
	while (i < 100)
	{
		//PARA BLOQUEAR Y DESBLOQUEAR UNA SECCIÓN
		//pasamos la dirrección de mmemmoria del mutex
		pthread_mutex_lock(&philo->sim->mutex);
		philo->sim->test += 1;
		pthread_mutex_unlock(&philo->sim->mutex);
		i++;
	}*/
	printf("hola hilo %i\n", philo->sim->test);
	if (philo->n_philo % 2 != 0)
	{
		if (philo->p_to_eat > philo->p_to_die)
		{
			sleeping(philo->p_to_die, philo->sim);
			//usleep(philo->p_to_die);
		}
		else
		{
			sleeping(philo->p_to_eat, philo->sim);
			//usleep(philo->p_to_eat * 1000);
		}
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
	/*	if (philo->n_philo % 2 != 0)
		{
			to_think(philo, philo->sim);
		}*/
		//if (philo->sim->t_must_eat <= 0 || philo->sim->test <= 0) ///!!!!!!
		//if (philo->sim->test <= 0) ///!!!!!!
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
	//INICIALIZAMOS EL MUTEX
	//dirección de memoria del mutex
	//argumentos
	pthread_mutex_init(&sim->mutex, NULL);
	pthread_mutex_init(&sim->mutex_print, NULL);

	sim->t_must_eat = (sim->n_philos * sim->t_must_eat) - 1;
	if (sim->t_must_eat == 0)
		sim->t_must_eat = -1;
	printf("times_to_eat: %li\n", sim->t_must_eat);

	//CREAMOS EL HILO
	//direccion de memoria del hilo
	//estructura especificadora de las caracteristicas del hilo
	//funcion con las tareas del hilo
	//parámetros de la función
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

	//CONDICIONES DE CARRERA
	//EVITAR QUE EL HILO TERMINE ANTES QUE OTRO O QUE NO HAYA TERMINADO AL FINAL
	//nombre del hilo a esperar
	//valor que esperamos que devuelva la funcion que ejecuta el hilo al terminar
	//(hay que poner la variable donde se va a ejecutar eel hilo al terminar)
	i = 0;
	while (i < sim->n_philos)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}

	printf("times_to_eat: %li\n", sim->t_must_eat);
	//DESTRUIMOS EL MUTEX
	//direccion de memoria del mutex
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