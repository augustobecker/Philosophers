/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:40:08 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:13:36 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error(char *message);

int	error(char *message)
{
	printf(GREY"philosophers : %s\n"RESET, message);
	exit (EXIT_FAILURE);
}
