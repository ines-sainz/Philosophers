/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:41:08 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/15 09:41:10 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	check_input(char *argv)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	input = ft_strtrim(argv, " \t");
	while (input[i])
	{
		if (ft_isdigit(input[i]) == 0 && input[i] != '+')
			return (free(input), 1);
		if (input[i] == '+')
			if (input[i + 1] == '+' || (i != 0
					&& ft_isdigit(input[i - 1]) == 1))
				return (free(input), 1);
		i++;
	}
	j = 0;
	while ((input[j] == '+' || input[j] == '0') && input[j + 1] == '0')
		j++;
	if ((i - j) > 12)
		return (free(input), 1);
	return (free(input), 0);
}

int	parse(char **argv, t_simulation *sim)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (check_input(argv[i]) == 1)
			return (1);
		i++;
	}
	sim->n_philos = ft_atol(argv[1]);
	sim->t_to_die = ft_atol(argv[2]);
	sim->t_to_eat = ft_atol(argv[3]);
	sim->t_to_sleep = ft_atol(argv[4]);
	if (i == 6)
	{
		sim->t_must_eat = ft_atol(argv[5]);
		if (sim->t_must_eat >= INT_MAX || sim->t_must_eat == 0)
			return (1);
	}
	if (sim->n_philos >= INT_MAX || sim->n_philos == 0
		|| sim->t_to_die >= INT_MAX || sim->t_to_die == 0
		|| sim->t_to_eat >= INT_MAX || sim->t_to_eat == 0
		|| sim->t_to_sleep >= INT_MAX || sim->t_to_sleep == 0)
		return (1);
	return (0);
}
