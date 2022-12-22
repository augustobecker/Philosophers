/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dinner_must_go_on.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:25:19 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 18:28:56 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool		dinner_must_go_on(t_philo *philo, t_action action);
static int	dies_during_an_action(t_philo *philo, t_action action);

t_bool	dinner_must_go_on(t_philo *philo, t_action action)
{
	long int	last_meal_time;

	last_meal_time = get_elapsed_time(&philo->last_meal);
	if (last_meal_time >= philo->time_to_die)
		return (false);
	else if ((action == EATING)
		&& (last_meal_time + philo->time_to_eat >= philo->time_to_die))
		return (dies_during_an_action(philo, EATING));
	else if ((action == SLEEPING)
		&& (last_meal_time + philo->time_to_sleep >= philo->time_to_die))
		return (dies_during_an_action(philo, SLEEPING));
	return (true);
}

static int	dies_during_an_action(t_philo *philo, t_action action)
{
	philosopher_log(philo, action);
	usleep((philo->time_to_die - get_elapsed_time(&philo->last_meal)) \
	* MILLI_TO_MICROSECND);
	return (0);
}
