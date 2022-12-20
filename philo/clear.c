/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:04:34 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:09:22 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_the_room(t_data *data, t_philo **chairs, t_fork **table);
void	clear_table(t_fork **table, int forks_nbr);

void	clear_the_room(t_data *data, t_philo **chairs, t_fork **table)
{
	clear_table(table, data->nbr_of_philo);
	free(chairs);
}

void	clear_table(t_fork **table, int forks_nbr)
{
	int	i;

	i = 0;
	while (i < forks_nbr)
	{
		free(table[i]);
		i++;
	}
	free(table);
}
