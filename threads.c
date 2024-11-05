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

pthread_mutex_t	mutex; //inicializarlo de manera global

void	*do_smth(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	printf("hola hilos %li\n", sim->n_philos);

	//PARA BLOQUEAR Y DESBLOQUEAR UNA SECCIÓN
	//pasamos la dirrección de mmemmoria del mutex
	int i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&mutex);
		sim->n_philos += 1;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	printf("des                    pues %li\n", sim->n_philos);

	return (NULL);
}

int	create_threads(t_simulation sim)
{
	pthread_t		thread;
	pthread_t		thread2;
	int				created;

	(void)sim;

	//INICIALIZAMOS EL MUTEX
	//dirección de memoria del mutex
	//argumentos
	pthread_mutex_init(&mutex, NULL);

	//CREAMOS EL HILO
	//direccion de memoria del hilo
	//estructura especificadora de las caracteristicas del hilo
	//funcion con las tareas del hilo
	//parámetros de la función
	printf("n_philos= %li\n", sim.n_philos);
	created = pthread_create(&thread, NULL, do_smth, (void *)(&sim));
	printf("n_philos200000000000000000000= %li\n", sim.n_philos);
	created = pthread_create(&thread2, NULL, do_smth, (void *)(&sim));
	printf("n_philos200000000000000000000= %li\n", sim.n_philos);

	if (created != 0)
		return (1);

	//CONDICIONES DE CARRERA
	//EVITAR QUE EL HILO TERMINE ANTES QUE OTRO O QUE NO HAYA TERMINADO AL FINAL
	//nombre del hilo a esperar
	//valor que esperamos que devuelva la funcion que ejecuta el hilo al terminar
	//(hay que poner la variable donde se va a ejecutar eel hilo al terminar)
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);

	//DESTRUIMOS EL MUTEX
	//direccion de memoria del mutex
	pthread_mutex_destroy(&mutex);
	return (0);
}