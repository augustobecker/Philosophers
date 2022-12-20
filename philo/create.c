/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 03:51:14 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:12:37 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*create_data(int argc, char *const *argv);
t_fork	**create_table(int forks_nbr);
t_fork	*create_fork(int fork_nbr);
t_philo	**create_chairs(int philos_nbr);
t_philo	*create_philosopher(t_data *data, t_fork **table, int nbr);

t_data	*create_data(int argc, char *const *argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error("malloc error");
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atolongi(argv[2]);
	data->time_to_eat = ft_atolongi(argv[3]);
	data->time_to_sleep = ft_atolongi(argv[4]);
	if (argc == MAX_ARGS_NBR)
	{
		data->count_meals = true;
		data->meals_per_philo = ft_atoi(argv[5]);
	}
	else
	{
		data->count_meals = false;
		data->meals_per_philo = 0;
	}
	data->a_philo_died = false;
	return (data);
}

t_fork	**create_table(int forks_nbr)
{
	t_fork	**table;

	table = malloc(sizeof(t_fork *) * forks_nbr);
	if (!table)
		error("malloc error");
	return (table);
}

t_fork	*create_fork(int fork_nbr)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		error("malloc error");
	new->nbr = fork_nbr;
	new->state = AVAILABLE;
	return (new);
}

t_philo	**create_chairs(int philos_nbr)
{
	t_philo	**chairs;

	chairs = malloc(sizeof(t_philo *) * philos_nbr);
	if (!chairs)
		error("malloc error");
	return (chairs);
}

t_philo	*create_philosopher(t_data *data, t_fork **table, int nbr)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		error("malloc error");
	new->nbr = nbr;
	new->action = SLEEPING;
	new->left_fork = table[nbr];
	if (nbr == data->nbr_of_philo - 1)
		new->right_fork = table[0];
	else
		new->right_fork = table[nbr + 1];
	new->data = data;
	return (new);
}
