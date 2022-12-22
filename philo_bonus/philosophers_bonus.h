/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:32:04 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 23:27:51 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include "defines.h"
# include "types.h"

void		arguments_validation(int argc, char *const *argv);

void		handle_sigint(int sig);

void		prepare_for_dinner(t_philo *philo);
void		start_dinner(t_philo *philo, sem_t *sem);
int			dinner(t_philo *philo, sem_t *table);
void		end_of_dinner(int *pid, int processes_nbr);

t_philo		*create_philosopher(int argc, char *const *argv);

long int	ft_atolongi(const char *str);
int			ft_atoi(const char *str);
int			ft_isdigit(int argument);

void		start_counting_time(t_philo *philo);
long int	get_elapsed_time(struct timeval *start);

void		takes_a_fork(t_philo *philo);
int			eats(t_philo *philo);
int			thinks(t_philo *philo);
int			sleeps(t_philo *philo);
int			dies(t_philo *philo);

t_bool		dinner_must_go_on(t_philo *philo, t_action action);

void		philosopher_log(t_philo *philo, t_action action);

int			error(char *message);

#endif