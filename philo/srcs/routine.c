/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:10:59 by repinat           #+#    #+#             */
/*   Updated: 2022/08/30 18:55:46 by repinat          ###   ########.fr       */
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
	usleep(1000);
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
	pthread_mutex_lock(&philo->last_eat_m);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->last_eat_m);
	if (philo->data_back->time_to_die < philo->data_back->time_to_eat)
		usleep(philo->data_back->time_to_die * 1000);
	else
		usleep(philo->data_back->time_to_eat * 1000);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_back->printing);
	printing(3, philo);
	pthread_mutex_unlock(&philo->data_back->printing);
	unlock_fork(philo);
	pthread_mutex_lock(&philo->data_back->booleen_died_mutex);
	if (philo->data_back->booleen_died == 1)
	{
		pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data_back->booleen_died_mutex);
	if (philo->data_back->time_to_die < philo->data_back->time_to_sleep)
		usleep(philo->data_back->time_to_die * 1000);
	else
		usleep(philo->data_back->time_to_sleep * 1000);
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_lock(&tmp->data_back->printing);
	pthread_mutex_unlock(&tmp->data_back->printing);
	if (tmp->philo_id % 2 == 0)
		usleep(50000);
	while (1)
	{
		pthread_mutex_lock(&tmp->data_back->booleen_died_mutex);
		if (tmp->data_back->booleen_died == 1)
		{
			pthread_mutex_unlock(&tmp->data_back->booleen_died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&tmp->data_back->booleen_died_mutex);
		is_eating(tmp);
		is_sleeping(tmp);
		is_thinking(tmp);
	}
	return (NULL);
}
