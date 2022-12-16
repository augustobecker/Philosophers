/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:27:40 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/15 17:41:29 by acesar-l         ###   ########.fr       */
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

#endif