#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	int	philo_id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	left_fork;
	int	right_fork;
	int	number_of_times_each_philosophers_must_eat;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		*threads;
	int				n_philo;
	int				fork_number;
	int				philo_number;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eating;
	pthread_mutex_t	printing;
}	t_data;



#endif