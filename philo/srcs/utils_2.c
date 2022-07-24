/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:06:33 by repinat           #+#    #+#             */
/*   Updated: 2022/06/02 15:06:35 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	lock_fork(t_philo *philo)
{
	if (philo->philo_id != 1)
		pthread_mutex_lock(&philo->fork);
	else
		pthread_mutex_lock(&philo->data_back->philos[philo->philo_id].fork);
	pthread_mutex_lock(&philo->data_back->printing);
	printing(1, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_lock(&philo->data_back->philos[0].fork);
	else if (philo->philo_id == 1)
		pthread_mutex_lock(&philo->data_back->philos[philo->philo_id - 1].fork);
	else
		pthread_mutex_lock(&philo->data_back->philos[philo->philo_id].fork);
	pthread_mutex_lock(&philo->data_back->printing);
	printing(1, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
}

void	unlock_fork(t_philo *philo)
{
	if (philo->philo_id != 1)
		pthread_mutex_unlock(&philo->fork);
	else
		pthread_mutex_unlock(&philo->data_back->philos[philo->philo_id].fork);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_unlock(&philo->data_back->philos[0].fork);
	else if (philo->philo_id == 1)
		pthread_mutex_unlock(&philo->data_back
			->philos[philo->philo_id - 1].fork);
	else
		pthread_mutex_unlock(&philo->data_back->philos[philo->philo_id].fork);
}

void	free_and_destroy(t_data *data)
{
	int	i;

	usleep(500);
	pthread_mutex_lock(&data->waiting);
	pthread_mutex_unlock(&data->waiting);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->philos[i].last_eat_m);
	pthread_mutex_destroy(&data->booleen_died_mutex);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->calcul_ms_mutex);
	free(data->philos);
}

void	my_error_message(char *message)
{
	ft_putstr_fd(message, 1);
	exit(-42);
}
