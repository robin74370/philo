/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:09:18 by repinat           #+#    #+#             */
/*   Updated: 2022/08/30 17:06:32 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_died_count(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].last_eat_m);
	if (data->philos[i].eat_count >= data->number_eat_each_philo)
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

void	check_inputs(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				my_error_message("Wrong inputs\n");
			j++;
		}
		i++;
	}
}
