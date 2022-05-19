#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				last_eat;
	int				eat_count;
	int				status;
	int				died;
	pthread_mutex_t	fork;
	t_data			*data_back;
}	t_philo;

struct s_data
{
	t_philo			*philos;
	int				n_philo;
	int				time;
	int				time_to_eat;
	int				died_count;
	int				time_to_die;
	int				time_to_sleep;
	int				number_eat_each_philo;
	int				num_each_philo_count;
	int				booleen_died;
	pthread_mutex_t	eating;
	pthread_mutex_t	printing;
};

long 				calcul_ms();
int					ft_atoi(const char *nptr);
void				ft_putstr_fd(char *str, int fd);
void				my_error_message(char *message);
void				is_eating(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				is_thinking(t_philo *philo);
//void				ft_usleep(int time);
unsigned long long	time_conversion();

#endif