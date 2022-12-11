/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning_pthreads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:31:40 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/11 20:07:46 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg);
void	launch_threads(void);
void	learning_pthreads(void);

// Execute things in parallel using Threads!

// A fork duplicates the whole process, duplicate all variables, that can be manipulated individually 
// Multiple threads can run in a process.
// Threads have common address space for variables, all threads can access all variables
// Threads are sharing memories 

void	learning_pthreads(void)
{
	launch_threads();
}

void	launch_threads(void)
{
    pthread_t		thread_one;
    pthread_t		thread_two;
	pthread_mutex_t	mutex;
    char			*return_value;

	pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread_one, NULL, &routine, (void *)"Thread one"))
        printf("Couldn't create a thread\n");
    if (pthread_create(&thread_two, NULL, &routine, (void *)"Thread two"))
        printf("Couldn't create a thread\n");
    pthread_join(thread_one, (void **)&return_value);
	printf(CYAN"[thread return] :"RESET" %s\n", return_value);
    pthread_join(thread_two, (void **)&return_value);
	printf(CYAN"[thread return] :"RESET" %s\n", return_value);
	pthread_mutex_destroy(&mutex);
    return ;
}

void	*routine(void *arg)
{
	// mutex only sensitive content or it loses the point to use multi threads at all
	//pthread_mutex_lock(&mutex);
    if (arg)
		printf(YELLOW"[thread] :"RESET" %s\n", (char *)arg);
    sleep(2);
    printf(GREY"[thread] : "RESET"Ending thread\n");
	//pthread_mutex_unlock(&mutex);
    return ("Success");
}