/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:25:41 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 18:35:13 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void		start_dinner(t_philo *philo, sem_t *sem);
static int	*alloc_pid(int processess_nbr);
static void	multiprocess(int *pid, int procs_nbr, t_philo *philo, sem_t *sem);
static void	wait_philos_to_eat_their_meals(int *pid, int processes_nbr);
static void	stop_simulation_when_a_philo_dies(int *pid, int processes_nbr);

void	start_dinner(t_philo *philo, sem_t *sem)
{
	int	*pid;

	pid = alloc_pid(philo->nbr_of_philo);
	multiprocess(pid, philo->nbr_of_philo, philo, sem);
	if (philo->count_meals)
		wait_philos_to_eat_their_meals(pid, philo->nbr_of_philo);
	else
		stop_simulation_when_a_philo_dies(pid, philo->nbr_of_philo);
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
			dinner(philo, sem);
			sem_close(sem);
			exit (0);
		}
		i++;
	}
}

static void	wait_philos_to_eat_their_meals(int *pid, int processes_nbr)
{
	int	i;

	i = 0;
	while (i < processes_nbr)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

static void	stop_simulation_when_a_philo_dies(int *pid, int processes_nbr)
{
	int	terminated;
	int	i;

	i = 0;
	terminated = waitpid(-1, NULL, 0);
	while (i < processes_nbr)
	{
		if (pid[i] != terminated)
			kill(pid[i], SIGINT);
		i++;
	}
}
