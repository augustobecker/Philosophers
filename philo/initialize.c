/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:21:53 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 03:58:15 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void        initialize(t_data *data, int argc, char *const *argv);
static void init_struct(t_data *data, int argc, char *const*argv);

void initialize(t_data *data, int argc, char *const *argv)
{
    
    init_struct(data, argc, argv);
}

void init_struct(t_data *data, int argc, char *const*argv)
{
    data->nbr_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_longatoi(argv[2]);
    data->time_to_eat = ft_longatoi(argv[3]);
    data->time_to_sleep = ft_longatoi(argv[4]);
    if (argc == MAX_ARGS_NBR)
    {
        data->count_meals = true;
        data->meals_per_philo = ft_atoi(argv[5]);
    }
    else
    {
        data->count_meals = false;
        data->meals_per_philo = 0;
    }
    data->a_philo_died = false;
}
