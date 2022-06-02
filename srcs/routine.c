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
		if (tmp->data_back->booleen_died == 1)
			return (NULL);
		is_eating(tmp);
		is_sleeping(tmp);
		is_thinking(tmp);
	}
	return (NULL);
}
