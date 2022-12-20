/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_validations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:38:04 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 14:35:10 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void        arguments_validation(int argc, char *const *argv);
static void check_arguments_nbr(int argc);
static void check_for_a_non_numeric_parameter(int argc, char *const *argv);

void arguments_validation(int argc, char *const *argv)
{
    check_arguments_nbr(argc);
    check_for_a_non_numeric_parameter(argc, argv);
}

static void check_arguments_nbr(int argc)
{
    if (argc < MIN_ARGS_NBR || argc > MAX_ARGS_NBR)
        error("Incorret number of arguments\n\n" RESET
            "usage:\n"
            "       ./philo\n"
            "       [number of philosophers]\n"
            "       [time to die]\n" 
            "       [time to eat]\n" 
            "       [time to sleep]\n"
            "       [number of times each philosopher must eat] -- Optional");
}

static void check_for_a_non_numeric_parameter(int argc, char *const *argv)
{
    int i;
    int j;

    i = 1;
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
