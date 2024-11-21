/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:12:51 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:52 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error(int i)
{
	if (i == 1)
		write(2, "Only 4 or 5 arguments.\n", 24);
	if (i == 2)
		write(2, "The arguments can only be a positive int above 0.\n", 51);
	if (i == 3)
		write(2, "Problem setting philosophers.\n", 31);
	if (i == 4)
		write(2, "Problem setting forks.\n", 24);
	if (i == 5)
		write(2, "Problem creating threads.\n", 27);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc != 5 && argc != 6)
		return (error(1));
	sim.philos = NULL;
	sim.t_must_eat = 0;
	sim.loop = 0;
	if (parse(argv, &sim) == 1)
		return (error(2));
	if (set_philos(&sim) == 1)
		return (error(3));
	if (create_threads(&sim) == 1)
	{
		free(sim.philos);
		return (error(5));
	}
	free(sim.philos);
	return (0);
}
