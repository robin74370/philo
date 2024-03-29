/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:02:40 by repinat           #+#    #+#             */
/*   Updated: 2022/05/19 16:13:34 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	calcul_ms(t_data *data)
{
	static long		start;

	(void)data;
	if (!start)
		start = time_conversion();
	return (time_conversion() - start);
}

unsigned long long	time_conversion(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], fd);
}

void	ft_clear(char **av)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi(av[2]) * 1000);
	printf("%d 1 died\n", ft_atoi(av[2]) + 1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}
