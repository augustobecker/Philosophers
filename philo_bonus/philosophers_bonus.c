/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:58:34 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 18:38:26 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char *const *argv)
{
	t_philo	*philosopher;

	arguments_validation(argc, argv);
	philosopher = create_philosopher(argc, argv);
	prepare_for_dinner(philosopher);
	free(philosopher);
}

t_philo	*create_philosopher(int argc, char *const *argv)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		error("malloc error");
	new->nbr = 0;
	new->nbr_of_philo = ft_atoi(argv[1]);
	new->time_to_die = ft_atolongi(argv[2]);
	new->time_to_eat = ft_atolongi(argv[3]);
	new->time_to_sleep = ft_atolongi(argv[4]);
	if (argc == MAX_ARGS_NBR)
	{
		new->count_meals = true;
		new->meals_per_philo = ft_atoi(argv[5]);
	}
	else
	{
		new->count_meals = false;
		new->meals_per_philo = 0;
	}
	new->action = SLEEPING;
	return (new);
}

int	error(char *message)
{
	printf(GREY"philosophers : %s\n"RESET, message);
	exit (EXIT_FAILURE);
}
