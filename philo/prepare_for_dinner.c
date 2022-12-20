/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_dinner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:00:34 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:40:41 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			prepare_for_dinner(t_data *data);
static void		set_the_table(t_fork **table, int forks_nbr);
static void		acommodate_philos(t_data *data, \
t_philo **chairs, t_fork **table);
static t_bool	should_philos_eat(t_data *data);

void	prepare_for_dinner(t_data *data)
{
	t_fork	**table;
	t_philo	**chairs;

	if (!should_philos_eat(data))
		return ;
	table = create_table(data->nbr_of_philo);
	set_the_table(table, data->nbr_of_philo);
	chairs = create_chairs(data->nbr_of_philo);
	acommodate_philos(data, chairs, table);
	start_dinner(data, chairs);
	clear_the_room(data, chairs, table);
}

static void	set_the_table(t_fork **table, int forks_nbr)
{
	int	i;

	i = 0;
	while (i < forks_nbr)
	{
		table[i] = create_fork(i);
		i++;
	}
}

static void	acommodate_philos(t_data *data, \
t_philo **chairs, t_fork **table)
{
	int		i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		chairs[i] = create_philosopher(data, table, i);
		i++;
	}
}

static t_bool	should_philos_eat(t_data *data)
{
	if ((data->count_meals)
		&& (data->meals_per_philo) == 0)
		return (false);
	return (true);
}
