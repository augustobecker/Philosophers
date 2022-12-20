/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:27:40 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/18 05:35:44 by acesar-l         ###   ########.fr       */
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

// void initialize(t_data *data, int argc, char **argv);
// void init_struct(t_data *data, int argc, char **argv);
void arguments_validation(int argc, char *const *argv);
void    initialize(t_data *data, int argc, char *const*argv);
int error(char *message);

// utils
long int	ft_longatoi(const char *str);
int         ft_atoi(const char *str);

//learning
void learning_pthreads(void);

//routine OK
void	*dinner(void *philosopher);

// time_utils OK
void start_counting_time(t_philo *philo);
long int get_elapsed_time(struct timeval *start);

//log OK
void philosopher_log(t_philo *philo, t_action action);

//actions OK
void	takes_a_fork(t_philo *philo, t_fork *fork);
int		eats(t_philo *philo);
int		thinks(t_philo *philo);
int		sleeps(t_philo *philo);
int		dies(t_philo *philo);

// OK
t_bool	dinner_must_go_on(t_philo *philo, t_action action);

#endif