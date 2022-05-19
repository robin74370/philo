/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:10:59 by repinat           #+#    #+#             */
/*   Updated: 2022/05/19 16:12:32 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	printing(4, philo);
}

void	is_eating(t_philo *philo)
{	
	pthread_mutex_lock(&philo->fork);
	if (philo->philo_id == philo->data_back->n_philo)
	{
		printing(1, philo);
		pthread_mutex_lock(&philo->data_back->philos[0].fork);
	}
	else
	{
		printing(1, philo);
		pthread_mutex_lock(&philo->data_back->philos[philo->philo_id].fork);
	}
	printing(2, philo);
	philo->last_eat = calcul_ms();
	philo->eat_count++;
	usleep(philo->data_back->time_to_eat * 1000);
}

void	is_sleeping(t_philo *philo)
{
	int	id_tmp;

	id_tmp = philo->philo_id;
	pthread_mutex_unlock(&philo->fork);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_unlock(&philo->data_back->philos[0].fork);
	else
		pthread_mutex_unlock(&philo->data_back->philos[id_tmp].fork);
	printing(3, philo);
	usleep(philo->data_back->time_to_sleep * 1000);
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_lock(&tmp->data_back->printing);
	pthread_mutex_unlock(&tmp->data_back->printing);
	if (tmp->data_back->n_philo % 2 == 0 && tmp->philo_id % 2 == 0)
		usleep(tmp->data_back->time_to_eat);
	else if (tmp->data_back->n_philo % 2 == 1)
		usleep(tmp->data_back->time_to_eat * (tmp->philo_id % 3));
	tmp->last_eat = calcul_ms();
	while (1)
	{
		is_eating(tmp);
		is_sleeping(tmp);
		is_thinking(tmp);
		if (tmp->philo_id % 2 != 0)
			usleep(100);
	}
	return (NULL);
}
