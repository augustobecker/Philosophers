/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_dinner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:32:10 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 18:34:29 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void			prepare_for_dinner(t_philo *philo);
static sem_t	*set_the_table(int forks_nbr);
static t_bool	should_philos_eat(t_philo *philo);
static void		clear_the_table(sem_t *table);

void	prepare_for_dinner(t_philo *philo)
{
	sem_t	*table;

	if (!should_philos_eat(philo))
		return ;
	table = set_the_table(philo->nbr_of_philo);
	start_dinner(philo, table);
	clear_the_table(table);
}

static sem_t	*set_the_table(int forks_nbr)
{
	sem_t	*semaphore;

	sem_unlink(SEM_FORKS_FNAME);
	semaphore = sem_open(SEM_FORKS_FNAME, O_CREAT, S_IRWXU | S_IRWXG, \
	forks_nbr);
	if (semaphore == SEM_FAILED)
		error("couldn't create the semaphore");
	return (semaphore);
}

static t_bool	should_philos_eat(t_philo *philo)
{
	if ((philo->count_meals)
		&& (philo->meals_per_philo) == 0)
		return (false);
	return (true);
}

static void	clear_the_table(sem_t *table)
{
	sem_close(table);
	sem_unlink(SEM_FORKS_FNAME);
}
