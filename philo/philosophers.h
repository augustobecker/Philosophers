/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:27:40 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 14:37:09 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include "defines.h"
# include "types.h"

void        arguments_validation(int argc, char *const *argv);
int         error(char *message);

void        prepare_for_dinner(t_data *data);
void        start_dinner(t_data *data, t_philo **philosopher);
void	    *dinner(void *philosopher);

t_data      *create_data(int argc, char *const *argv);
t_fork      **create_table(int forks_nbr);
t_fork      *create_fork(int fork_nbr);
t_philo     **create_chairs(int philos_nbr);
t_philo     *create_philosopher(t_data *data, t_fork **table, int nbr);

void        clear_the_room(t_data *data, t_philo **chairs, t_fork **table);
void        clear_table(t_fork **table, int forks_nbr);

long int	ft_atolongi(const char *str);
int         ft_atoi(const char *str);
int			ft_isdigit(int argument);

void        start_counting_time(t_philo *philo);
long int    get_elapsed_time(struct timeval *start);

void 	    takes_a_fork(t_philo *philo, t_fork *fork);
int		    eats(t_philo *philo);
int		    thinks(t_philo *philo);
int	    	sleeps(t_philo *philo);
int		    dies(t_philo *philo);

t_bool	    dinner_must_go_on(t_philo *philo, t_action action);

void        philosopher_log(t_philo *philo, t_action action);

#endif