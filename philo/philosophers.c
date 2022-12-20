/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:26:19 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 13:46:27 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char *const *argv)
{
    t_data *data;
    
    arguments_validation(argc, argv);
    data = create_data(argc, argv);
    prepare_for_dinner(data);
    free(data);
}
