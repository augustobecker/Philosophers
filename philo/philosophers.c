/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:26:19 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/16 05:21:10 by acesar-l         ###   ########.fr       */
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
void destroy_thread(pthread_t thread);
long int get_elapsed_time(struct timeval *start);
void print_philos(t_philo **chairs);

void get_time(void);

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
	// chairs[3]->left_fork->state = IN_USE;
	// chairs[1]->action = SLEEPING;
	//print_struct(data);
	//print_philos(chairs);
	//pthread_mutex_init(&(data->mutex), NULL);
	start_dinner(data, chairs);
	//pthread_mutex_destroy(&(data->mutex));
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
    new->timestamp = 0;
    new->action = SLEEPING;
	new->left_fork = table[nbr];
	if (nbr != data->nbr_of_philo - 1)
		new->right_fork = table[nbr + 1];
	else
		new->right_fork = table[0];
	new->data = data;
    return (new);
}

void start_dinner(t_data *data, t_philo **philosopher)
{
    pthread_t   *thread;
	int i;
    
	i = 0;
    thread = malloc(sizeof(pthread_t) * data->nbr_of_philo);
	while (i < data->nbr_of_philo)
    {
        launch_thread(thread[i], philosopher[i]);
        i++;
    }
    i = 0;
    sleep(3);
    while (i < data->nbr_of_philo)
    {
        destroy_thread(thread[i]);
        i++;
    }
}

void philosopher_log(long int elapsed_time, t_philo *philo, t_action action)
{
    philo->action = action;
    printf(YELLOW"  	%ld	"WHITE\
    "%d ", elapsed_time, philo->nbr);
    if (action == TAKING_FORK)
        printf(BLUE"has taken a fork\n"RESET);
    else if (action == EATING)
        printf(CYAN"is eating\n"RESET);
    else if (action == SLEEPING)
        printf(GREY"is sleeping\n"RESET);
    else if (action == THINKING)
        printf(PURPLE"is thinking\n"RESET);
    else    
        printf(RED"died\n"RESET);
}

void	*routine_philo(void *arg)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *) arg;
    data = philo->data;
    gettimeofday(&philo->start_time, NULL);
    while ((get_elapsed_time(&philo->start_time) <= data->time_to_die)
    && (!data->a_philo_died))
    {
        if ((philo->left_fork->state == AVAILABLE)
        && (philo->right_fork->state == AVAILABLE))
        {
            pthread_mutex_lock(&data->mutex);
            philo->left_fork->state = IN_USE;
            philosopher_log(get_elapsed_time(&philo->start_time), philo, TAKING_FORK);
            philo->right_fork->state = IN_USE;
            philosopher_log(get_elapsed_time(&philo->start_time), philo, TAKING_FORK);
            pthread_mutex_unlock(&data->mutex);
            philosopher_log(get_elapsed_time(&philo->start_time), philo, EATING);
            usleep(data->time_to_eat);
            philo->left_fork->state = AVAILABLE;
            philo->right_fork->state = AVAILABLE;
            philosopher_log(get_elapsed_time(&philo->start_time), philo, SLEEPING);
            usleep(data->time_to_sleep);
        }
        if (philo->action != THINKING)
            philosopher_log(get_elapsed_time(&philo->start_time), philo, THINKING);
    }
	(*data).a_philo_died = true;
	philosopher_log(get_elapsed_time(&philo->start_time), philo, DIE);
    return ("Success");
}

/*
void	*routine_philo(void *arg)
{
    t_philo *philo;
    t_data *data;
    long int time;
	// mutex only sensitive content or it loses the point to use multi threads at all
    philo = (t_philo *) arg;
    data = *(philo->data);
    gettimeofday(&philo->start_time, NULL);
    printf("[Philosopher] [%d]\n", philo->nbr);
    //time = get_elapsed_time(&philo->start_time);
    //printf("%ld milliseconds\n", get_elapsed_time(&philo->start_time));
    time = 0;
    while (time < data->time_to_die)
    {
        //time = get_elapsed_time(&philo->start_time);
    //pthread_mutex_lock(&mutex);
	//pthread_mutex_unlock(&mutex);
        time = get_elapsed_time(&philo->start_time);
    }
    return ("Success");
}
*/

long int get_elapsed_time(struct timeval *start)
{
    struct timeval current;
    
    gettimeofday(&current, NULL);
    return (((current.tv_sec - (*start).tv_sec) * SECND_TO_MILLISECND) \
    + (current.tv_usec - (*start).tv_usec));
}

/*
void	*routine_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    while ()
    //pthread_mutex_lock(&mutex);
	//pthread_mutex_unlock(&mutex);
    return ("Success");
}
*/

void launch_thread(pthread_t thread, t_philo *philosopher)
{
    pthread_create(&thread, NULL, &routine_philo, (void *)philosopher);
}

void destroy_thread(pthread_t thread)
{
    pthread_join(thread, NULL);
}

/*
void *philosopher_routine(void *philo)
{
	t_data *data;

	data = *(philo->data);
	while (time < data->time_to_die)
}
*/
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
		printf("	[timestamp]: %d\n", chairs[i]->timestamp);
		i++;
	}
	printf("\n");
}

/*
void get_time(void)
{
    struct timeval beginning;
    struct timeval current_time;
    long int    time_passed;

    gettimeofday(&beginning, NULL);
    printf("seconds: %ld | milliseconds : %ld\n", beginning.tv_sec, beginning.tv_usec);
    gettimeofday(&current_time, NULL);
    printf("seconds: %ld | milliseconds : %ld\n", current_time.tv_sec, current_time.tv_usec);
    time_passed = ((current_time.tv_sec - beginning.tv_sec) / 1000) + (current_time.tv_usec - beginning.tv_usec );
    printf("%ld milliseconds passed\n", time_passed);
}
*/

// vamos ter que pegar o horário original do começo da operação
// sempre que precisar atualizar, pegar o horário de novo
// subtrair do original e ver se bate.
// seconds - seconds = tempo ->converter para milli
// milli - milli = tempo
// somar seconds + milli