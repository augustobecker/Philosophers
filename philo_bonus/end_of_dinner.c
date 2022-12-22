/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:13:07 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 23:29:24 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void		end_of_dinner(int *pid, int processes_nbr);
static void	wait_philos_eat_their_meal(int *pid, int procs_nbr, int term_proc);
static void	stop_simulation(int *pid, int processes_nbr, int term_proc);
static int	a_philo_died(int proc_exit_code);

void	end_of_dinner(int *pid, int processes_nbr)
{
	int	terminated_proc;
	int	wstatus;

	terminated_proc = waitpid(ANY_CHILD_PROC, &wstatus, 0);
	if (a_philo_died(wstatus))
		stop_simulation(pid, processes_nbr, terminated_proc);
	else
		wait_philos_eat_their_meal(pid, processes_nbr, terminated_proc);
}

static int	a_philo_died(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (1);
}

static void	wait_philos_eat_their_meal(int *pid, int procs_nbr, int term_proc)
{
	int	i;

	i = 0;
	while (i < procs_nbr)
	{
		if (pid[i] != term_proc)
			waitpid(pid[i], NULL, 0);
		i++;
	}
}

static void	stop_simulation(int *pid, int processes_nbr, int term_proc)
{
	int	i;

	i = 0;
	while (i < processes_nbr)
	{
		if (pid[i] != term_proc)
			kill(pid[i], SIGINT);
		i++;
	}
}
