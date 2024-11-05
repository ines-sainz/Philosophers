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
	t_simulation *sim;

	sim = (t_simulation *)arg;

	//PARA BLOQUEAR Y DESBLOQUEAR UNA SECCIÓN
	//pasamos la dirrección de mmemmoria del mutex
	int i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&sim->mutex);
		sim->test += 1;
		pthread_mutex_unlock(&sim->mutex);
		i++;
	}
	printf("hola hilo %i\n", sim->test);

	return (NULL);
}

int	create_threads(t_simulation sim)
{
	int				created;

	(void)sim;

	//INICIALIZAMOS EL MUTEX
	//dirección de memoria del mutex
	//argumentos
	pthread_mutex_init(&sim.mutex, NULL);

	//CREAMOS EL HILO
	//direccion de memoria del hilo
	//estructura especificadora de las caracteristicas del hilo
	//funcion con las tareas del hilo
	//parámetros de la función
	printf("n_philos= %li\n", sim.n_philos);
	sim.p_iterator = sim.first_philo;
	while (sim.p_iterator)
	{
		created = pthread_create(&(sim.p_iterator->thread_id), NULL, do_smth, (void *)(&sim));
		if (created != 0)
			return (1);
		printf("created philo %i\n", sim.p_iterator->n_philo);
		sim.p_iterator = sim.p_iterator->next;
	}

	//CONDICIONES DE CARRERA
	//EVITAR QUE EL HILO TERMINE ANTES QUE OTRO O QUE NO HAYA TERMINADO AL FINAL
	//nombre del hilo a esperar
	//valor que esperamos que devuelva la funcion que ejecuta el hilo al terminar
	//(hay que poner la variable donde se va a ejecutar eel hilo al terminar)
	sim.p_iterator = sim.first_philo;
	while (sim.p_iterator)
	{
		pthread_join(sim.p_iterator->thread_id, NULL);
		sim.p_iterator = sim.p_iterator->next;
	}

	//DESTRUIMOS EL MUTEX
	//direccion de memoria del mutex
	pthread_mutex_destroy(&sim.mutex);
	return (0);
}