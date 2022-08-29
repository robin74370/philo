/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:06:33 by repinat           #+#    #+#             */
/*   Updated: 2022/08/29 14:46:26 by repinat          ###   ########.fr       */
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

/*
void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->data_back->printing);
	printing(1, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
	if (philo->philo_id == 1)
	{
		pthread_mutex_lock(&philo->data_back
			->philos[philo->data_back->n_philo - 1].fork);
		pthread_mutex_lock(&philo->data_back->printing);
		printing(1, philo);
		pthread_mutex_unlock(&philo->data_back->printing);
	}
	else
	{
		pthread_mutex_lock(&philo->data_back
			->philos[philo->philo_id - 2]. fork);
		pthread_mutex_lock(&philo->data_back->printing);
		printing(1, philo);
		pthread_mutex_unlock(&philo->data_back->printing);
	}
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->philo_id == 1)
		pthread_mutex_unlock(&philo->data_back
			->philos[philo->data_back->n_philo - 1].fork);
	else
		pthread_mutex_unlock(&philo->data_back
			->philos[philo->philo_id - 2]. fork);
}
*/
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

void	affichage(int code, t_philo *philo)
{
	unsigned long long	time;

	pthread_mutex_lock(&philo->data_back->calcul_ms_mutex);
	time = calcul_ms(philo->data_back);
	pthread_mutex_unlock(&philo->data_back->calcul_ms_mutex);
	if (code == 1)
		printf("%llu %d has taken a fork\n", time, philo->philo_id);
	if (code == 2)
		printf("%llu %d is eating\n", time, philo->philo_id);
	if (code == 3)
		printf("%llu %d is sleeping\n", time, philo->philo_id);
	if (code == 4)
		printf("%llu %d is thinking\n", time, philo->philo_id);
	if (code == 5)
	{
		printf("%llu %d died\n", time, philo->philo_id);
		pthread_mutex_lock(&philo->data_back->booleen_died_mutex);
		philo->data_back->booleen_died = 1;
		pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
	}
}
