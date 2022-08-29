/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:03:03 by repinat           #+#    #+#             */
/*   Updated: 2022/08/29 14:17:44 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				last_eat;
	int				eat_count;
	int				died;
	pthread_mutex_t	fork;
	pthread_mutex_t	last_eat_m;
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
	pthread_mutex_t	calcul_ms_mutex;
	pthread_mutex_t	booleen_died_mutex;
	pthread_mutex_t	printing;
	pthread_mutex_t	waiting;
};

unsigned long long	time_conversion(void);
void				ft_clear(char **av);
void				*routine(void *philo);
long				calcul_ms(t_data *data);
void				is_eating(t_philo *philo);
void				lock_fork(t_philo *philo);
int					ft_atoi(const char *nptr);
void				check_data_3(t_data *data);
void				unlock_fork(t_philo *philo);
void				is_thinking(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				free_and_destroy(t_data *data);
void				check_inputs(int ac, char **av);
void				ft_putstr_fd(char *str, int fd);
void				my_error_message(char *message);
void				check_data_2(t_data *data, int i);
void				printing(int code, t_philo *philo);
void				check_died_count(t_data *data, int i);
void				affichage(int code, t_philo *philo);


#endif