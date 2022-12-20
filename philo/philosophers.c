/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:26:19 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/20 03:46:05 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    create_philosophers(t_data *data);
void    print_struct(t_data *data);

void starting(t_data *data);
t_fork **create_table(int forks_nbr);
t_fork  *create_fork(int fork_nbr);
void    set_the_table(t_fork **table, int forks_nbr);
t_philo **create_chairs(int philos_nbr);
void	acommodate_philosophers(t_data *data, t_philo **chairs, t_fork **table);
t_philo *create_philosopher(t_data *data, t_fork **table, int nbr);
void start_dinner(t_data *data, t_philo **philosopher);
void launch_thread(pthread_t thread, t_philo *philosopher);
//void destroy_thread(pthread_t thread);
void destroy_thread(pthread_t *thread);
long int get_elapsed_time(struct timeval *start);
void print_philos(t_philo **chairs);

void get_time(void);

void clear_the_room(t_data *data, t_philo **chairs, t_fork **table);
void clear_table(t_fork **table, int forks_nbr);

int main(int argc, char *const *argv)
{
    t_data *data;
    
    arguments_validation(argc, argv);
    data = malloc(sizeof(t_data));
    initialize(data, argc, argv);
    starting(data);
    //create_philosophers(data);
    //learning_pthreads();
    return (EXIT_SUCCESS);
}

void starting(t_data *data)
{
    t_fork  **table;
    t_philo **chairs;
    
    table = create_table(data->nbr_of_philo);
    set_the_table(table, data->nbr_of_philo);
    chairs = create_chairs(data->nbr_of_philo);
    acommodate_philosophers(data, chairs, table);
	// chairs[1]->left_fork->state = IN_USE;
    // chairs[1]->right_fork->state = IN_USE;
	// chairs[1]->action = SLEEPING;
	//print_struct(data);
	// print_philos(chairs);
    // chairs[1]->left_fork->state = AVAILABLE;
    // chairs[1]->right_fork->state = AVAILABLE;
	start_dinner(data, chairs);
    clear_the_room(data, chairs, table);
}

void clear_the_room(t_data *data, t_philo **chairs, t_fork **table)
{
    clear_table(table, data->nbr_of_philo);
    free(chairs);
    free(data);
}

void clear_table(t_fork **table, int forks_nbr)
{
    int i;

    i = 0;
    while (i < forks_nbr)
    {
        free(table[i]);
        i++;
    }
    free(table);
}

t_fork **create_table(int forks_nbr)
{
    t_fork     **table;

    table = malloc(sizeof(t_fork *) * forks_nbr);
    if (!table)
        error("malloc error");
    return (table);
}

void    set_the_table(t_fork **table, int forks_nbr)
{
    int i;

    i = 0;
    while (i < forks_nbr)
    {
        table[i] = create_fork(i);
        i++;
    }
}

t_fork  *create_fork(int fork_nbr)
{
    t_fork *new;

    new = malloc(sizeof(t_fork));
    if (!new)
        error("malloc error");
    new->nbr = fork_nbr;
    new->state = AVAILABLE;
    return (new);
}

t_philo **create_chairs(int philos_nbr)
{
    t_philo **chairs;

    chairs = malloc(sizeof(t_philo *) * philos_nbr);
    if (!chairs)
        error("malloc error");
    return (chairs);
}

void	acommodate_philosophers(t_data *data, t_philo **chairs, t_fork **table)
{
    int i;
    
    i = 0;
    while (i < data->nbr_of_philo)
    {
        chairs[i] = create_philosopher(data, table, i);
        i++;
    }
}

t_philo *create_philosopher(t_data *data, t_fork **table, int nbr)
{
    t_philo *new;

    new = malloc(sizeof(t_philo));
    if (!new)
        error("malloc error");
    new->nbr = nbr;
    new->action = SLEEPING;
	new->left_fork = table[nbr];
	if (nbr == data->nbr_of_philo - 1)
        new->right_fork = table[0];
	else
        new->right_fork = table[nbr + 1];
	new->data = data;
    return (new);
}

void finish_dinner(t_data *data, pthread_t **threads)
{
    int i;

    i = 0;
    while (i < data->nbr_of_philo)
    {
        pthread_join((*threads)[i], NULL);
        i++;
    }
}

void start_dinner(t_data *data, t_philo **philosopher)
{
    pthread_t   *thread;
	int i;
    int philos;
    
	i = 0;
    pthread_mutex_init(&(data->mutex), NULL);
    thread = malloc(sizeof(pthread_t) * data->nbr_of_philo);
    philos = data->nbr_of_philo;
	while (i < data->nbr_of_philo)
    {
        pthread_create(&thread[i], NULL, &dinner, (void *)(*philosopher));
        i++;
    }
    i = 0;
    while (i < philos)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
}

// void philosopher_log(long int elapsed_time, t_philo *philo, t_action action)
// {
//     philo->action = action;
//     printf(YELLOW"  	%ld	"WHITE
//     "%d ", elapsed_time, philo->nbr + 1);
//     if (action == TAKING_FORK)
//         printf(BLUE"has taken a fork\n"RESET);
//     else if (action == EATING)
//         printf(CYAN"is eating\n"RESET);
//     else if (action == SLEEPING)
//         printf(GREY"is sleeping\n"RESET);
//     else if (action == THINKING)
//         printf(PURPLE"is thinking\n"RESET);
//     else    
//         printf(RED"died\n"RESET);
// }

// void	*routine_philo(void *arg)
// {
//     t_philo *philo;
//     t_data *data;
//     int     meals;
//     struct timeval  start_time;
//     struct timeval	time_to_die;
    
//     philo = (t_philo *) arg;
//     data = philo->data;
//     gettimeofday(&start_time, NULL);
//     gettimeofday(&time_to_die, NULL);
//     meals = 0;
//     while ((get_elapsed_time(&time_to_die) <= data->time_to_die)
//     && (!data->a_philo_died))
//     {
//         if ((philo->left_fork->state == AVAILABLE)
//         && (philo->right_fork->state == AVAILABLE))
//         {
//             pthread_mutex_lock(&data->mutex);
//             philo->left_fork->state = IN_USE;
//             philosopher_log(get_elapsed_time(&start_time), philo, TAKING_FORK);
//             philo->right_fork->state = IN_USE;
//             philosopher_log(get_elapsed_time(&start_time), philo, TAKING_FORK);
//             pthread_mutex_unlock(&data->mutex);
//             philosopher_log(get_elapsed_time(&start_time), philo, EATING);
//             usleep(data->time_to_eat * MILLI_TO_MICROSECND);
//             gettimeofday(&time_to_die, NULL);
//             meals++;
//             if (data->meals_per_philo != -1 && data->meals_per_philo == meals)
//                 break ;
//             philo->left_fork->state = AVAILABLE;
//             philo->right_fork->state = AVAILABLE;
//             philosopher_log(get_elapsed_time(&start_time), philo, SLEEPING);
//             usleep(data->time_to_sleep * MILLI_TO_MICROSECND);
//         }
//         if (philo->action != THINKING)
//             philosopher_log(get_elapsed_time(&start_time), philo, THINKING);
//     }
// 	(*data).a_philo_died = true;
// 	philosopher_log(get_elapsed_time(&start_time), philo, DIE);
//     free(philo);
//     return ("Success");
// }

void    print_struct(t_data *data)
{
    printf("[Struct data]\n [%d (philos)] [%ld (die)] [%ld (eat)] [%ld (sleep)] [%d (meals)]\n", \
    data->nbr_of_philo, data->time_to_die, data->time_to_eat, \
    data->time_to_sleep, data->meals_per_philo);
}

void print_philos(t_philo **chairs)
{
	int i;
	t_data *data;

	i = 0;
	data = ((*chairs)->data);
	while (i < data->nbr_of_philo)
	{
		printf("[Philosopher] [%d]: \n", chairs[i]->nbr);
		if (chairs[i]->action == THINKING)
			printf("	[THINKING]\n");
		else if (chairs[i]->action == EATING)
			printf("	[EATING]\n");
		else
			printf("	[SLEEPING]\n");
		if (chairs[i]->left_fork->state == AVAILABLE)
			printf(GREEN"	[left_fork]\n"RESET);
		else
			printf(RED"	[left_fork]\n"RESET);
		if (chairs[i]->right_fork->state == AVAILABLE)
			printf(GREEN"	[right_fork]\n"RESET);
		else
			printf(RED"	[right_fork]\n"RESET);
		i++;
	}
	printf("\n");
}
