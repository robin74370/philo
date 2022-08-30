/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:02:28 by repinat           #+#    #+#             */
/*   Updated: 2022/08/30 18:15:13 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(int code, t_philo *philo)
{
	pthread_mutex_lock(&philo->data_back->booleen_died_mutex);
	if (philo->data_back->booleen_died == 1 && code != 5
		&& (philo->data_back->number_eat_each_philo == -1
			|| philo->data_back->num_each_philo_count
			!= philo->data_back->n_philo))
	{
		pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
	affichage(code, philo);
}

void	check_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i <= data->n_philo)
	{
		if (i == data->n_philo)
			i = 0;
		usleep(100);
		pthread_mutex_lock(&data->calcul_ms_mutex);
		if (calcul_ms(data) - data->philos[i].last_eat >= data->time_to_die)
		{
			check_data_2(data, i);
			return ;
		}
		if (data->number_eat_each_philo != -1)
			check_died_count(data, i);
		if (data->num_each_philo_count >= data->n_philo)
		{
			check_data_3(data);
			return ;
		}
		pthread_mutex_unlock(&data->calcul_ms_mutex);
	}
}

void	thread_creation(t_data *data)
{
	int			i;

	pthread_mutex_init(&data->calcul_ms_mutex, NULL);
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->booleen_died_mutex, NULL);
	pthread_mutex_init(&data->waiting, NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_init(&data->philos[i].fork, NULL);
		pthread_mutex_init(&data->philos[i].last_eat_m, NULL);
	}
	i = -1;
	pthread_mutex_lock(&data->printing);
	while (++i < data->n_philo)
		pthread_create(&data->philos[i].thread,
			NULL, &routine, &data->philos[i]);
	pthread_mutex_unlock(&data->printing);
	check_data(data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philos[i].thread, NULL);
	free_and_destroy(data);
}

int	init_struct(t_data *data, int ac, char **av)
{
	int	i;

	data->philos = malloc((data->n_philo) * sizeof(t_philo));
	if (!data->philos)
		return (0);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_eat_each_philo = ft_atoi(av[5]) + 1;
	else
		data->number_eat_each_philo = -1;
	i = -1;
	while (++i < data->n_philo)
	{
		data->philos[i].last_eat = 0;
		data->philos[i].philo_id = i + 1;
		data->philos[i].data_back = data;
		data->philos[i].died = 0;
		data->philos[i].eat_count = 0;
	}
	data->num_each_philo_count = 0;
	data->booleen_died = 0;
	return (0);
}

int	main(int ac, char **av)
{	
	t_data	data;

	if (!(ac >= 5 && ac <= 6))
		my_error_message("Wrong number of arguments\n");
	check_inputs(ac, av);
	if (ac == 6 && ft_atoi(av[5]) == 0)
		return (0);
	if (ft_atoi(av[1]) == 1)
	{
		ft_clear(av);
		return (0);
	}
	data.n_philo = atoi(av[1]);
	if (data.n_philo < 1)
		my_error_message("Incorrect inputs\n");
	if (init_struct(&data, ac, av) == 1)
		return (0);
	if (data.n_philo != 1)
		thread_creation(&data);
	return (0);
}
