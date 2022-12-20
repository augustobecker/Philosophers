/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:27:44 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:38:21 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "philosophers.h"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_state
{
	AVAILABLE,
	IN_USE
}	t_state;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DIE
}	t_action;

typedef struct s_fork
{
	int			nbr;
	t_state		state;
}	t_fork;

typedef struct s_data
{
	int				nbr_of_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	t_bool			count_meals;
	int				meals_per_philo;
	t_bool			a_philo_died;
	pthread_mutex_t	mutex;
}	t_data;

typedef struct s_philo
{
	int				nbr;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_action		action;
	struct timeval	start;
	struct timeval	last_meal;
	t_data			*data;
}	t_philo;

#endif