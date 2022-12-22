/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:25:41 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 23:26:15 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void		start_dinner(t_philo *philo, sem_t *sem);
static int	*alloc_pid(int processess_nbr);
static void	multiprocess(int *pid, int procs_nbr, t_philo *philo, sem_t *sem);

void	start_dinner(t_philo *philo, sem_t *sem)
{
	int	*pid;

	pid = alloc_pid(philo->nbr_of_philo);
	multiprocess(pid, philo->nbr_of_philo, philo, sem);
	end_of_dinner(pid, philo->nbr_of_philo);
	free(pid);
}

static int	*alloc_pid(int processess_nbr)
{
	int	*pid;

	pid = malloc(sizeof(int) * processess_nbr);
	return (pid);
}

static void	multiprocess(int *pid, int procs_nbr, t_philo *philo, sem_t *sem)
{
	int	a_philo_died;
	int	i;

	i = 0;
	while (i < procs_nbr)
	{
		pid[i] = 1;
		if (pid[i])
			pid[i] = fork();
		if (!pid[i])
		{
			free(pid);
			philo->nbr += i;
			a_philo_died = dinner(philo, sem);
			sem_close(sem);
			exit (a_philo_died);
		}
		i++;
	}
}
