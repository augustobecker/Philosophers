/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:27:35 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 04:49:50 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void start_dinner(t_data *data, t_philo **philosopher);
static pthread_t   *alloc_threads(int nbr_of_threads);
static void launch_threads(pthread_t *thread, int thrds_nbr, t_philo **philo);
static void threads_end(pthread_t *thread, int threads_nbr);

void start_dinner(t_data *data, t_philo **philosopher)
{
    pthread_t   *thread;

    pthread_mutex_init(&data->mutex, NULL);
    thread = alloc_threads(data->nbr_of_philo);
    launch_threads(thread, data->nbr_of_philo, philosopher);
    threads_end(thread, data->nbr_of_philo);
    pthread_mutex_destroy(&data->mutex);
    free(thread);
}

static pthread_t   *alloc_threads(int nbr_of_threads)
{
    pthread_t   *threads;

    threads = malloc(sizeof(pthread_t) * nbr_of_threads);
    if (!threads)
        error("malloc error");
    return (threads);
}
static void launch_threads(pthread_t *thread, int thrds_nbr, t_philo **philo)
{
    int i;

    i = 0;
    while (i < thrds_nbr)
    {
        pthread_create(&thread[i], NULL, &dinner, (void *)philo[i]);
        i++;
    }
}

static void threads_end(pthread_t *thread, int threads_nbr)
{
    int i;

    i = 0;
    while (i < threads_nbr)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
}