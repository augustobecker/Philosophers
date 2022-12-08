/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:26:19 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/08 20:16:55 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char *const *argv)
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
    if (*argv == NULL)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}