#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	left_fork;
	int	right_fork;
	int	number_of_times_each_philosophers_must_eat;
}	t_philo;

typedef struct s_data
{
	int				philo_number;
	int				fork_number;
	pthread_t		*threads;
	int				n_philo;
	t_philo			*philos;
	pthread_mutex_t	printing;
	pthread_mutex_t	eating;
	pthread_mutex_t	*fork;
}	t_data;



#endif