/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:01:46 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 15:18:23 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		philosopher_log(t_philo *philo, t_action action);
static void	print_log(long int timestamp, int philo, char *message);

void	philosopher_log(t_philo *philo, t_action action)
{
	long int	elapsed_time;

	elapsed_time = get_elapsed_time(&philo->start);
	if (action == TAKING_FORK)
		print_log(elapsed_time, philo->nbr + 1, BLUE"has taken a fork");
	else if (action == EATING)
		print_log(elapsed_time, philo->nbr + 1, CYAN"is eating");
	else if (action == SLEEPING)
		print_log(elapsed_time, philo->nbr + 1, GREY"is sleeping");
	else if (action == THINKING)
		print_log(elapsed_time, philo->nbr + 1, PURPLE"is thinking");
	else if (action == DIE)
		print_log(elapsed_time, philo->nbr + 1, RED"died");
}

static void	print_log(long int timestamp, int philo, char *message)
{
	printf(YELLOW"  	%ld	"WHITE"%d %s\n"RESET, timestamp, philo, message);
}
