/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:39:27 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:22:27 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_a_fork(t_philo *philo, t_fork *fork);
int		eats(t_philo *philo);
int		thinks(t_philo *philo);
int		sleeps(t_philo *philo);
int		dies(t_philo *philo);

void	takes_a_fork(t_philo *philo, t_fork *fork)
{
	fork->state = IN_USE;
	philo->action = TAKING_FORK;
	philosopher_log(philo, TAKING_FORK);
}

int	eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!dinner_must_go_on(philo, EATING))
	{
		dies(philo);
		return (1);
	}
	philo->action = EATING;
	philosopher_log(philo, EATING);
	usleep(data->time_to_eat * MILLI_TO_MICROSECND);
	gettimeofday(&philo->last_meal, NULL);
	philo->left_fork->state = AVAILABLE;
	philo->right_fork->state = AVAILABLE;
	return (0);
}

int	thinks(t_philo *philo)
{
	if (!dinner_must_go_on(philo, THINKING))
	{
		dies(philo);
		return (1);
	}
	else if (philo->action != THINKING)
		philosopher_log(philo, THINKING);
	philo->action = THINKING;
	return (0);
}

int	sleeps(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!dinner_must_go_on(philo, SLEEPING))
	{
		dies(philo);
		return (1);
	}
	philo->action = SLEEPING;
	philosopher_log(philo, SLEEPING);
	usleep(data->time_to_sleep * MILLI_TO_MICROSECND);
	return (0);
}

int	dies(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo->action = DIE;
	pthread_mutex_lock(&data->mutex);
	if (!data->a_philo_died)
		philosopher_log(philo, DIE);
	pthread_mutex_unlock(&data->mutex);
	(*data).a_philo_died = true;
	return (0);
}
