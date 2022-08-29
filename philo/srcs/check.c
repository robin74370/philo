/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:09:18 by repinat           #+#    #+#             */
/*   Updated: 2022/08/29 14:41:08 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_died_count(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].last_eat_m);
	if (data->philos[i].eat_count == data->number_eat_each_philo)
		data->num_each_philo_count++;
	pthread_mutex_unlock(&data->philos[i].last_eat_m);
}

void	check_data_2(t_data *data, int i)
{
	pthread_mutex_lock(&data->booleen_died_mutex);
	data->booleen_died = 1;
	pthread_mutex_unlock(&data->booleen_died_mutex);
	pthread_mutex_unlock(&data->calcul_ms_mutex);
	pthread_mutex_lock(&data->waiting);
	pthread_mutex_unlock(&data->waiting);
	pthread_mutex_lock(&data->printing);
	printing(5, &data->philos[i]);
	pthread_mutex_unlock(&data->printing);
	return ;
}

void	check_data_3(t_data *data)
{
	pthread_mutex_lock(&data->booleen_died_mutex);
	data->booleen_died = 1;
	pthread_mutex_unlock(&data->booleen_died_mutex);
	pthread_mutex_lock(&data->waiting);
	pthread_mutex_unlock(&data->waiting);
	pthread_mutex_unlock(&data->calcul_ms_mutex);
	return ;
}
