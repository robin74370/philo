#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	philo_id;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		*threads;
	int				n_philo;
	int				time;
	int				time_to_eat;
	int				died_count;
	int				time_to_die;
	int				time_to_sleep;
	int				number_of_times_each_philosophers_must_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eating;
	pthread_mutex_t	printing;
}	t_data;

int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *str, int fd);
void	my_error_message(char *message);
void	is_sleeping(int philo_id, t_data *data);
void	is_thinking(int philo_id, t_data *data);
void	is_eating(int philo_id, t_data *data);

#endif