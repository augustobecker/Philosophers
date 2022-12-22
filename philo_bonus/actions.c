/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:28:02 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 01:54:29 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	takes_a_fork(t_philo *philo);
int		eats(t_philo *philo);
int		thinks(t_philo *philo);
int		sleeps(t_philo *philo);
int		dies(t_philo *philo);

void	takes_a_fork(t_philo *philo)
{
	philo->action = TAKING_FORK;
	philosopher_log(philo, TAKING_FORK);
}

int	eats(t_philo *philo)
{
	if (!dinner_must_go_on(philo, EATING))
	{
		dies(philo);
		return (1);
	}
	philo->action = EATING;
	philosopher_log(philo, EATING);
	usleep(philo->time_to_eat * MILLI_TO_MICROSECND);
	gettimeofday(&philo->last_meal, NULL);
	return (0);
}

int	thinks(t_philo *philo)
{
	if (!dinner_must_go_on(philo, THINKING))
	{
		dies(philo);
		return (1);
	}
	philosopher_log(philo, THINKING);
	philo->action = THINKING;
	return (0);
}

int	sleeps(t_philo *philo)
{
	if (!dinner_must_go_on(philo, SLEEPING))
	{
		dies(philo);
		return (1);
	}
	philo->action = SLEEPING;
	philosopher_log(philo, SLEEPING);
	usleep(philo->time_to_sleep * MILLI_TO_MICROSECND);
	return (0);
}

int	dies(t_philo *philo)
{
	philo->action = DIE;
	philosopher_log(philo, DIE);
	return (0);
}
