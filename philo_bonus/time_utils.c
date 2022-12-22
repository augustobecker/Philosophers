/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:24:27 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/21 03:24:34 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long int	get_elapsed_time(struct timeval *start);
void		start_counting_time(t_philo *philo);

long int	get_elapsed_time(struct timeval *start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec - (*start).tv_sec) * SECND_TO_MILLISECND) \
	+ (current.tv_usec - (*start).tv_usec) / MICRO_TO_MILLISECND);
}

void	start_counting_time(t_philo *philo)
{
	gettimeofday(&philo->start, NULL);
	gettimeofday(&philo->last_meal, NULL);
}
