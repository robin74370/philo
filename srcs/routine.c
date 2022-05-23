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
	printing(4, philo);
}

void	is_eating(t_philo *philo)
{	
	pthread_mutex_lock(&philo->fork);
	printing(1, philo);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_lock(&philo->data_back->philos[0].fork);
	else
		pthread_mutex_lock(&philo->data_back->philos[philo->philo_id].fork);
	printing(2, philo);
	philo->eat_count++;
	philo->last_eat = calcul_ms();
	usleep(philo->data_back->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_unlock(&philo->data_back->philos[0].fork);
	else
		pthread_mutex_unlock(&philo->data_back->philos[philo->philo_id].fork);
}

void	is_sleeping(t_philo *philo)
{
	printing(3, philo);
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
//	else if (tmp->data_back->n_philo % 2 == 1)
//		usleep(tmp->data_back->time_to_eat * (tmp->philo_id % 3));
//	tmp->last_eat = calcul_ms();
	while (1)
	{
		is_eating(tmp);
		is_sleeping(tmp);
		is_thinking(tmp);
//		if (tmp->philo_id % 2 != 0)
//			usleep(100);
	}
	return (NULL);
}

void	free_and_destroy(t_data *data)
{
	int	i;

	i = -1;
	 
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->philos[i].fork);
	pthread_mutex_destroy(&data->printing);
	free(data->philos);
	exit (0);
}
