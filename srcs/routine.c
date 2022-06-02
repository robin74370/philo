/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:10:59 by repinat           #+#    #+#             */
/*   Updated: 2022/05/19 16:20:47 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_back->booleen_died_mutex);
	if (philo->data_back->booleen_died == 1)
	{
		pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
	pthread_mutex_lock(&philo->data_back->printing);
	printing(4, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
}

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
		pthread_mutex_unlock(&philo->data_back->philos[philo->philo_id - 1].fork);
	else
		pthread_mutex_unlock(&philo->data_back->philos[philo->philo_id].fork);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_back->booleen_died_mutex);
	if (philo->data_back->booleen_died == 1)
	{
		pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
	lock_fork(philo);
	pthread_mutex_lock(&philo->data_back->printing);
	printing(2, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
	pthread_mutex_lock(&philo->data_back->calcul_ms_mutex);
	philo->last_eat = calcul_ms(philo->data_back);
	pthread_mutex_unlock(&philo->data_back->calcul_ms_mutex);
	unlock_fork(philo);
	usleep(philo->data_back->time_to_eat * 1000);
	pthread_mutex_lock(&philo->last_eat_m);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->last_eat_m);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_back->booleen_died_mutex);
	if (philo->data_back->booleen_died == 1)
	{
		pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
	pthread_mutex_lock(&philo->data_back->printing);
	printing(3, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
	usleep(philo->data_back->time_to_sleep * 1000);
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_lock(&tmp->data_back->printing);
	pthread_mutex_unlock(&tmp->data_back->printing);
	if (tmp->philo_id % 2 == 0)
		usleep(tmp->data_back->time_to_eat * 1000);
	else if (tmp->data_back->n_philo % 2 == 1)
		usleep(tmp->data_back->time_to_eat * (tmp->philo_id % 3));
	while (1)
	{
	//	pthread_mutex_lock(&tmp->data_back->booleen_died_mutex);
		if (tmp->data_back->booleen_died == 1)
			return (NULL) ;
	//	pthread_mutex_unlock(&tmp->data_back->booleen_died_mutex);
		is_eating(tmp);
		is_sleeping(tmp);
		is_thinking(tmp);
//		if (tmp->philo_id % 2 != 0)
//			usleep(200);
	}
	return (NULL);
}

void	free_and_destroy(t_data *data)
{
	int	i;

	usleep(500);
	pthread_mutex_lock(&data->waiting);
	pthread_mutex_unlock(&data->waiting);
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philos[i].last_eat_m);
	//	pthread_mutex_destroy(&data->philos[i].fork);
	}
	pthread_mutex_destroy(&data->booleen_died_mutex);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->calcul_ms_mutex);
	free(data->philos);
//	exit (-42);
}
