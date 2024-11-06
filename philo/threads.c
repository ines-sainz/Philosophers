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

void	*do_smth(void *arg)
{
	t_philos *sim;

	sim = (t_philos *)arg;
	int i = 0;
	while (i < 10000)
	{
		//PARA BLOQUEAR Y DESBLOQUEAR UNA SECCIÓN
		//pasamos la dirrección de mmemmoria del mutex
		pthread_mutex_lock(&sim->sim->mutex);
		sim->sim->test += 1;
		pthread_mutex_unlock(&sim->sim->mutex);
		i++;
	}
	printf("hola hilo %i\n", sim->sim->test);
	printf("a %i\n", sim->n_philo);
	printf("b %li\n", sim->sim->t_must_eat);

	/*while (1)
	{
		if (sim.)
		if (sim->t_must_eat == 0)
			break ;
	}*/
	return (NULL);
}

int	create_threads(t_simulation *sim)
{
	int				created;
	int				i;

	(void)sim;

	//INICIALIZAMOS EL MUTEX
	//dirección de memoria del mutex
	//argumentos
	pthread_mutex_init(&sim->mutex, NULL);

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
	pthread_mutex_destroy(&sim->mutex);
	return (0);
}