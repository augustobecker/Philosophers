/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_dinner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:26:24 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 18:34:54 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void			*dinner(t_philo *philo, sem_t *table);
static void		put_both_forks_back_in_table(sem_t *sem);
int				action(t_philo *philo, sem_t *sem, t_action action);
static int		picks_up_both_forks(t_philo *philo, sem_t *table);
static t_bool	is_philo_satieted(t_philo *philo, int meals);

void	*dinner(t_philo *philosopher, sem_t *table)
{
	int	meals;

	meals = 0;
	start_counting_time(philosopher);
	while (true)
	{
		if (picks_up_both_forks(philosopher, table))
			break ;
		if (action(philosopher, table, EATING))
			break ;
		put_both_forks_back_in_table(table);
		meals++;
		if (is_philo_satieted(philosopher, meals))
			break ;
		if (action(philosopher, table, SLEEPING))
			break ;
		if (action(philosopher, table, THINKING))
			break ;
	}
	free(philosopher);
	return (0);
}

int	action(t_philo *philo, sem_t *sem, t_action action)
{
	if (action == TAKING_FORK)
		return (picks_up_both_forks(philo, sem));
	else if (action == EATING)
		return (eats(philo));
	else if (action == SLEEPING)
		return (sleeps(philo));
	else if (action == THINKING)
		return (thinks(philo));
	else if (action == DIE)
		return (dies(philo));
	else
		return (0);
}

static int	picks_up_both_forks(t_philo *philo, sem_t *sem)
{
	if (!dinner_must_go_on(philo, TAKING_FORK))
	{
		dies(philo);
		return (1);
	}
	sem_wait(sem);
	sem_wait(sem);
	takes_a_fork(philo);
	takes_a_fork(philo);
	return (0);
}

static void	put_both_forks_back_in_table(sem_t *sem)
{
	sem_post(sem);
	sem_post(sem);
}

static t_bool	is_philo_satieted(t_philo *philo, int meals)
{
	if ((philo->count_meals)
		&& (meals == philo->meals_per_philo))
		return (true);
	return (false);
}
