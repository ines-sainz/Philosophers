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

void	think(t_philos *philos, t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex_print);
	printf("%li im philo %i and im thinking\n", set_time() - sim->start_time, philos->n_philo);
	printf("%li set time\n", set_time());
	pthread_mutex_unlock(&sim->mutex_print);
	/*pthread_mutex_lock(&sim->mutex);
	sim->test--;
	pthread_mutex_unlock(&sim->mutex);*/
}

void	eat(t_philos *philos, t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex_print);
	sim->t_must_eat--;
	printf("%li im philo %i and im eating\n", set_time() - sim->start_time, philos->n_philo);
	pthread_mutex_unlock(&sim->mutex_print);
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

	while (1)
	{
		if (philo->n_philo % 2 != 0)
		{
			think(philo, philo->sim);
		}
		if (philo->n_philo % 2 == 0)
		{
			eat(philo, philo->sim);
		}
		//if (philo->sim->t_must_eat <= 0 || philo->sim->test <= 0) ///!!!!!!
		//if (philo->sim->test <= 0) ///!!!!!!
		if (philo->sim->t_must_eat <= 0)
			break ;
	}
	printf("out loop\n");
	return (NULL);
}

int	create_threads(t_simulation *sim)
{
	int				created;
	int				i;

	(void)sim;

	sim->start_time = set_time();

	printf ("start time %li\n", sim->start_time);
	//INICIALIZAMOS EL MUTEX
	//dirección de memoria del mutex
	//argumentos
	pthread_mutex_init(&sim->mutex, NULL);
	pthread_mutex_init(&sim->mutex_print, NULL);

	sim->t_must_eat = sim->n_philos * sim->t_must_eat;
	if (sim->t_must_eat == 0)
		sim->t_must_eat = -1;

	//CREAMOS EL HILO
	//direccion de memoria del hilo
	//estructura especificadora de las caracteristicas del hilo
	//funcion con las tareas del hilo
	//parámetros de la función
	printf("n_philos= %li\n", sim->n_philos);
	i = 0;
	while (i < sim->n_philos)
	{
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