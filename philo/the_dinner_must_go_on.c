/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dinner_must_go_on.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:02:27 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:34:45 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool		dinner_must_go_on(t_philo *philo, t_action action);
static int	dies_during_an_action(t_philo *philo, t_action action);

t_bool	dinner_must_go_on(t_philo *philo, t_action action)
{
	t_data		*data;
	long int	last_meal_time;

	data = philo->data;
	last_meal_time = get_elapsed_time(&philo->last_meal);
	if (data->a_philo_died)
		return (false);
	else if (last_meal_time >= data->time_to_die)
		return (false);
	else if ((action == EATING)
		&& (last_meal_time + data->time_to_eat >= data->time_to_die))
		return (dies_during_an_action(philo, EATING));
	else if ((action == SLEEPING)
		&& (last_meal_time + data->time_to_sleep >= data->time_to_die))
		return (dies_during_an_action(philo, SLEEPING));
	return (true);
}

static int	dies_during_an_action(t_philo *philo, t_action action)
{
	t_data	*data;

	data = philo->data;
	philosopher_log(philo, action);
	usleep((data->time_to_die - get_elapsed_time(&philo->last_meal)) \
	* MILLI_TO_MICROSECND);
	dies(philo);
	return (0);
}
