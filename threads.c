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
	printf("hola hilos %li\n", sim->n_philos);
	return (NULL);
}

int	create_threads(t_simulation sim)
{
	pthread_t	thread;
	int			created;

	(void)sim;

	//CREAMOS EL HILO
	//direccion de memoria del hilo
	//estructura especificadora de las caracteristicas del hilo
	//funcion con las tareas del hilo
	//parámetros de la función
	printf("n_philos= %li\n", sim.n_philos);
	created = pthread_create(&thread, NULL, do_smth, (void *)(&sim));
	if (created != 0)
		return (1);

	//CONDICIONES DE CARRERA
	//EVITAR QUE EL HILO TERMINE ANTES QUE OTRO O QUE NO HAYA TERMINADO AL FINAL
	//nombre del hilo a esperar
	//valor que esperamos que devuelva la funcion que ejecuta el hilo al terminar
	//(hay que poner la variable donde se va a ejecutar eel hilo al terminar)
	pthread_join(thread, NULL);
	return (0);
}