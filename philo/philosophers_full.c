#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

# define MIN_ARGS_NBR               5
# define MAX_ARGS_NBR               6

# define SECND_TO_MILLISECND        1000
# define MICRO_TO_MILLISECND        1000
# define MILLI_TO_MICROSECND        1000

# define BLACK				        "\033[0;30m"
# define RED				        "\033[0;31m"
# define GREEN				        "\033[0;32m"
# define YELLOW				        "\033[0;33m"
# define BLUE			    	    "\033[0;34m"
# define PURPLE				        "\033[0;35m"
# define CYAN				        "\033[0;36m"
# define WHITE				        "\033[0;37m"
# define GREY				        "\033[0;90m"
# define RESET				        "\033[0m"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_state
{
	AVAILABLE,
	IN_USE
}	t_state;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DIE
}	t_action;

typedef struct s_fork
{
	int			nbr;
	t_state		state;
} t_fork;

typedef struct s_data
{
    int				nbr_of_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	t_bool			count_meals;
	int				meals_per_philo;
	t_bool			a_philo_died;
	pthread_mutex_t	mutex;
} t_data;

typedef struct s_philo
{
	int				nbr;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_action		action;
	struct timeval	start;
	struct timeval	last_meal;
	t_data			*data;
} t_philo;

void        arguments_validation(int argc, char *const *argv);
static void check_arguments_nbr(int argc);
static void check_for_a_non_numeric_parameter(int argc, char *const *argv);

int         error(char *message);

void        prepare_for_dinner(t_data *data);
static void    set_the_table(t_fork **table, int forks_nbr);
static void	   acommodate_philos(t_data *data, t_philo **chairs, t_fork **table);
static t_bool should_philos_eat(t_data *data);

void        start_dinner(t_data *data, t_philo **philosopher);
static pthread_t   *alloc_threads(int nbr_of_threads);
static void launch_threads(pthread_t *thread, int thrds_nbr, t_philo **philo);
static void threads_end(pthread_t *thread, int threads_nbr);

void	    *dinner(void *philosopher);
static t_bool	are_both_forks_available(t_philo *philo);
static int		action(t_philo *philo, t_action action);
static int		picks_up_both_forks(t_philo *philo);
static t_bool	is_philo_satieted(t_philo *philo, int meals);

t_data      *create_data(int argc, char *const *argv);
t_fork      **create_table(int forks_nbr);
t_fork      *create_fork(int fork_nbr);
t_philo     **create_chairs(int philos_nbr);
t_philo     *create_philosopher(t_data *data, t_fork **table, int nbr);

void        clear_the_room(t_data *data, t_philo **chairs, t_fork **table);
void        clear_table(t_fork **table, int forks_nbr);

long int	ft_atolongi(const char *str);
int         ft_atoi(const char *str);
int			ft_isdigit(int argument);

void        start_counting_time(t_philo *philo);
long int    get_elapsed_time(struct timeval *start);

void 	    takes_a_fork(t_philo *philo, t_fork *fork);
int		    eats(t_philo *philo);
int		    thinks(t_philo *philo);
int	    	sleeps(t_philo *philo);
int		    dies(t_philo *philo);

t_bool	    dinner_must_go_on(t_philo *philo, t_action action);
static int	dies_during_an_action(t_philo *philo, t_action action);

void        philosopher_log(t_philo *philo, t_action action);
static void print_log(long int timestamp, int philo, char *message);

int main(int argc, char *const *argv)
{
    t_data *data;
    
    arguments_validation(argc, argv);
    data = create_data(argc, argv);
    prepare_for_dinner(data);
    free(data);
}

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

t_data *create_data(int argc, char *const *argv)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        error("malloc error");
    data->nbr_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atolongi(argv[2]);
    data->time_to_eat = ft_atolongi(argv[3]);
    data->time_to_sleep = ft_atolongi(argv[4]);
    if (argc == MAX_ARGS_NBR)
    {
        data->count_meals = true;
        data->meals_per_philo = ft_atoi(argv[5]);
    }
    else
    {
        data->count_meals = false;
        data->meals_per_philo = 0;
    }
    data->a_philo_died = false;
    return (data);
}

void prepare_for_dinner(t_data *data)
{
    t_fork  **table;
    t_philo **chairs;
    
    if (!should_philos_eat(data))
        return;
    table = create_table(data->nbr_of_philo);
    set_the_table(table, data->nbr_of_philo);
    chairs = create_chairs(data->nbr_of_philo);
    acommodate_philos(data, chairs, table);
    start_dinner(data, chairs);
    clear_the_room(data, chairs, table);
}

static void    set_the_table(t_fork **table, int forks_nbr)
{
    int i;

    i = 0;
    while (i < forks_nbr)
    {
        table[i] = create_fork(i);
        i++;
    }
}

static void	acommodate_philos(t_data *data, t_philo **chairs, t_fork **table)
{
    int i;
    
    i = 0;
    while (i < data->nbr_of_philo)
    {
        chairs[i] = create_philosopher(data, table, i);
        i++;
    }
}

static t_bool should_philos_eat(t_data *data)
{
    if ((data->count_meals)
    && (data->meals_per_philo) == 0)
        return (false);
    return (true);
}

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
        if (pthread_create(&thread[i], NULL, &dinner, (void *)philo[i]))
            error("couldn't create a thread");
        i++;
    }
}

static void threads_end(pthread_t *thread, int threads_nbr)
{
    int i;

    i = 0;
    while (i < threads_nbr)
    {
        if (pthread_join(thread[i], NULL))
            error("couldn't join a thread");
        i++;
    }
}

void	*dinner(void *philo)
{
    t_philo *philosopher;
    int meals;
    
    meals = 0;
    philosopher = (t_philo *) philo;
	start_counting_time(philo);
    while (true)
    {
        if (are_both_forks_available(philosopher))
        {
            action(philosopher, TAKING_FORK);
            if (action(philosopher, EATING))
				break;
            meals++;
            philosopher->left_fork->state = AVAILABLE;
            philosopher->right_fork->state = AVAILABLE;
            if (is_philo_satieted(philosopher, meals))
                break;
            else if (action(philosopher, SLEEPING))
				break;
        }
        if (action(philosopher, THINKING))
			break;
    }
    free(philosopher);
    return (0);
}

static t_bool are_both_forks_available(t_philo *philo)
{
    if (philo->left_fork == philo->right_fork)
        return (false);
    if ((philo->left_fork->state == AVAILABLE)
        && (philo->right_fork->state == AVAILABLE))
        return (true);
    return (false);    
}

int	action(t_philo *philo, t_action action)
{
	switch (action)
	{
		case (TAKING_FORK):
			return (picks_up_both_forks(philo));
		case (EATING):
			return (eats(philo));
		case (SLEEPING):
			return (sleeps(philo));
		case (THINKING):
			return (thinks(philo));
		case (DIE):
			return (dies(philo));
	}
	return (0);
}

static int    picks_up_both_forks(t_philo *philo)
{
	t_data *data;

	data = philo->data;
    if (!dinner_must_go_on(philo, TAKING_FORK))
	{
		dies(philo);
		return (1);
	}
    pthread_mutex_lock(&data->mutex);
    takes_a_fork(philo, philo->left_fork);
    takes_a_fork(philo, philo->right_fork);
    pthread_mutex_unlock(&data->mutex);
	return (0);
}

static t_bool is_philo_satieted(t_philo *philo, int meals)
{
    t_data *data;

	data = philo->data;
    if ((data->count_meals)
    	&& (meals == data->meals_per_philo))
        return (true);
    return (false);
}

long int get_elapsed_time(struct timeval *start)
{
    struct timeval current;
    
    gettimeofday(&current, NULL);
    return (((current.tv_sec - (*start).tv_sec) * SECND_TO_MILLISECND) \
    + (current.tv_usec - (*start).tv_usec) / MICRO_TO_MILLISECND);
}

void start_counting_time(t_philo *philo)
{
    gettimeofday(&philo->start, NULL);
    gettimeofday(&philo->last_meal, NULL);
}

void	takes_a_fork(t_philo *philo, t_fork *fork)
{
	fork->state = IN_USE;
	philo->action = TAKING_FORK;
	philosopher_log(philo, TAKING_FORK);
}

int	eats(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (!dinner_must_go_on(philo, EATING))
	{
		dies(philo);
		return (1);
	}
	philo->action = EATING;
	philosopher_log(philo, EATING);
	usleep(data->time_to_eat * MILLI_TO_MICROSECND);
	gettimeofday(&philo->last_meal, NULL);
	return (0);
}

int	thinks(t_philo *philo)
{
	if (!dinner_must_go_on(philo, THINKING))
	{
		dies(philo);
		return (1);
	}
	else if (philo->action != THINKING)
		philosopher_log(philo, THINKING);
	philo->action = THINKING;
	return (0);
}

int	sleeps(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (!dinner_must_go_on(philo, SLEEPING))
	{
		dies(philo);
		return (1);
	}
	philo->action = SLEEPING;
	philosopher_log(philo, SLEEPING);
	usleep(data->time_to_sleep * MILLI_TO_MICROSECND);
	return (0);
}

int	dies(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	philo->action = DIE;
	pthread_mutex_lock(&data->mutex);
	if (!data->a_philo_died)
		philosopher_log(philo, DIE);
	pthread_mutex_unlock(&data->mutex);
	(*data).a_philo_died = true;
	return (0);
}

t_bool	dinner_must_go_on(t_philo *philo, t_action action)
{
	t_data 		*data;
	long int	last_meal_time;

	data = philo->data;
	last_meal_time = get_elapsed_time(&philo->last_meal);
	if (data->a_philo_died)
		return (false);
	else if (last_meal_time >= data->time_to_die)
		return (false);
	else if ((action == EATING)
	&& (last_meal_time + data->time_to_eat >= data->time_to_die))
		return (dies_during_an_action(philo, EATING));
	else if ((action == SLEEPING)
	&& (last_meal_time + data->time_to_sleep >= data->time_to_die))
		return (dies_during_an_action(philo, SLEEPING));
	return (true);
}

static int	dies_during_an_action(t_philo *philo, t_action action)
{
	t_data	*data;

	data = philo->data;
	philosopher_log(philo, action);
	usleep((data->time_to_die - get_elapsed_time(&philo->last_meal)) * MILLI_TO_MICROSECND);
	dies(philo);
	return (0);
}

void philosopher_log(t_philo *philo, t_action action)
{
    long int elapsed_time;

    elapsed_time = get_elapsed_time(&philo->start);
    switch (action)
    {
        case (TAKING_FORK):
            print_log(elapsed_time, philo->nbr + 1, BLUE"has taken a fork");
        break;
		case (EATING):
            print_log(elapsed_time, philo->nbr + 1, CYAN"is eating");
        break;
		case (SLEEPING):
            print_log(elapsed_time, philo->nbr + 1, GREY"is sleeping");
        break;
		case (THINKING):
            print_log(elapsed_time, philo->nbr + 1, PURPLE"is thinking");
        break;
		case (DIE):
            print_log(elapsed_time, philo->nbr + 1, RED"died");
        break;
    }
}

static void print_log(long int timestamp, int philo, char *message)
{
    printf(YELLOW"  	%ld	"WHITE"%d %s\n"RESET, timestamp, philo, message);
}
