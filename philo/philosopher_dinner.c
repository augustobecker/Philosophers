/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_dinner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:10:07 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/18 05:35:12 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*dinner(void *philosopher);
static t_bool	are_both_forks_available(t_philo *philo);
static int		action(t_philo *philo, t_action action);
static int		picks_up_both_forks(t_philo *philo);
static t_bool	is_philo_satieted(t_philo *philo, int meals);

void	*dinner(void *philo)
{
    t_philo *philosopher;
    int meals;
    
    meals = 0;
    philosopher = (t_philo *) philo;
	start_counting_time(philo);
    while (true)
    {
        if (are_both_forks_available(philosopher))
        {
            action(philosopher, TAKING_FORK);
            if (action(philosopher, EATING))
				break;
            meals++;
            philosopher->left_fork->state = AVAILABLE;
            philosopher->right_fork->state = AVAILABLE;
            if (is_philo_satieted(philosopher, meals))
                break;
            else if (action(philosopher, SLEEPING))
				break;
        }
        if (action(philosopher, THINKING))
			break;
    }
    free(philosopher);
    return (0);
}

static t_bool are_both_forks_available(t_philo *philo)
{
    if ((philo->left_fork->state == AVAILABLE)
        && (philo->right_fork->state == AVAILABLE))
        return (true);
    return (false);    
}

int	action(t_philo *philo, t_action action)
{
	switch (action)
	{
		case (TAKING_FORK):
			return (picks_up_both_forks(philo));
		case (EATING):
			return (eats(philo));
		case (SLEEPING):
			return (sleeps(philo));
		case (THINKING):
			return (thinks(philo));
		case (DIE):
			return (dies(philo));
	}
	return (0);
}

static int    picks_up_both_forks(t_philo *philo)
{
	t_data *data;

	data = philo->data;
    pthread_mutex_lock(&data->mutex);
    takes_a_fork(philo, philo->left_fork);
    takes_a_fork(philo, philo->right_fork);
    pthread_mutex_unlock(&data->mutex);
	return (0);
}

static t_bool is_philo_satieted(t_philo *philo, int meals)
{
    t_data *data;

	data = philo->data;
    if ((data->count_meals)
    	&& (meals == data->meals_per_philo))
        return (true);
    return (false);
}
