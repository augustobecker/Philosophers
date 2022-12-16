/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_validations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:38:04 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/12 01:24:57 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void arguments_validation(int argc, char *const *argv);
static int	ft_isdigit(int argument);

void arguments_validation(int argc, char *const *argv)
{
    int i;
    int j;

    i = 1;
    if (argc < MIN_ARGS_NBR || argc > MAX_ARGS_NBR)
        error("Incorret number of arguments\n\n" RESET
            "usage:\n"
            "       ./philo\n"
            "       [number of philosophers]\n"
            "       [time to die]\n" 
            "       [time to eat]\n" 
            "       [time to sleep]\n"
            "       [number of times each philosopher must eat] -- Optional");
    while (i < argc)
    {
        j = 0;
        if (!argv[i][0])
            error("Null argument");
        while (argv[i][j])
            if (!ft_isdigit(argv[i][j++]))
                error("Not a valid parameter. Use positive Integers only");
        i++;
    }
}

static int	ft_isdigit(int argument)
{
	return (argument >= '0' && argument <= '9');
}
