/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:24:43 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/22 01:52:54 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "philosophers_bonus.h"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DIE
}	t_action;

typedef struct s_philo
{
	int				nbr;
	int				nbr_of_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	t_bool			count_meals;
	int				meals_per_philo;
	t_action		action;
	struct timeval	start;
	struct timeval	last_meal;
}	t_philo;

#endif