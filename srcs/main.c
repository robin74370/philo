#include "philo.h"

long calcul_ms()
{
	static long	start;

	if (!start)
		start = time_conversion();
	return (time_conversion() - start);
}

void	printing(int code, t_philo *philo)
{
	unsigned long long time;

	time = calcul_ms();
//	philo->last_eat = time;
//	printf("id : %d last eat : %d\n", philo->philo_id, philo->last_eat);
	if (code == 1)
		printf("%llu %d has taken a fork\n", time, philo->philo_id);
	if (code == 2)
		printf("%llu %d is eating\n", time, philo->philo_id);
	if (code == 3)
		printf("%llu %d is sleeping\n", time, philo->philo_id);
	if (code == 4)
		printf("%llu %d is thinking\n", time, philo->philo_id);
	if (code == 5)
		printf("%llu %d died\n", time, philo->philo_id);
}

void	check_died(t_data *data)
{
	if (data->died_count != 0)
		exit(-42);
}

void	is_thinking(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		usleep(((2 * philo->data_back->time_to_eat)
			- philo->data_back->time_to_sleep) * 1000);
	else
		usleep((philo->data_back->time_to_eat
			- philo->data_back->time_to_sleep));
	printing(4, philo);
	philo->status = 1;
}

void	is_eating(t_philo *philo)
{	
	int	id_tmp;
	static unsigned long long tmp;
	int	time;
	int	last;

	(void)last;
	time = calcul_ms();	
	if (!tmp)
		tmp = time_conversion();
	time = (time_conversion() - tmp);
	last = time - philo->last_eat;
	id_tmp = philo->philo_id;
	pthread_mutex_lock(&philo->fork);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_lock(&philo->data_back->philos[0].fork);
	else
		pthread_mutex_lock(&philo->data_back->philos[id_tmp].fork);
	printing(1, philo);
	printing(1, philo);
	printing(2, philo);
	philo->last_eat = calcul_ms();
	philo->eat_count++;
	usleep(philo->data_back->time_to_eat * 1000);
	philo->status = 2;
//	printf("after : %d\n", philo->last_eat);

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
//	int							id_tmp;	
	
//	id_tmp = philo->philo_id;
	usleep(philo->data_back->time_to_sleep);
	philo->status = 3;
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		if (tmp->status == 1)
			is_eating(tmp);
		if (tmp->status == 2)
			is_sleeping(tmp);
		if (tmp->status == 3)
			is_thinking(tmp);
//		if (tmp->philo_id % 2 == 0)
//			usleep(100);
	}
	return (NULL);
}

void	thread_creation(t_data *data)
{
	int			i;
	
	//data->time = time_conversion();
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->eating, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->philos[i].fork, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]);
	while (1)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			if (calcul_ms() - data->philos[i].last_eat >= data->time_to_die)
			{
				printing(5, &data->philos[i]);
				exit(-42);
			}
			if (data->number_eat_each_philo != -1)
			{
				if (data->philos[i].eat_count == data->number_eat_each_philo)
					data->num_each_philo_count++;
			}
			if (data->num_each_philo_count == data->number_eat_each_philo)
				exit (-42);
		}
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philos[i].thread, NULL);
}

void	init_struct(t_data *data, int ac, char **av)
{
	int	i;

	data->philos = malloc((data->n_philo) * sizeof(t_philo));
	if (!data->philos)
		return ;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_eat_each_philo = ft_atoi(av[5]);
	else
		data->number_eat_each_philo = -1;
	i = -1;
	while(++i < data->n_philo)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].data_back = data;
		data->philos[i].status = 1;
		data->philos[i].last_eat = 0;
		data->philos[i].died = 0;	
		data->philos[i].eat_count = -1;
	}
	data->num_each_philo_count = 0;
}

int	main(int ac, char **av)
{	
	t_data	data;

	if (!(ac >= 5 && ac <= 6))
		my_error_message("Wrong number of arguments\n");
	data.n_philo = atoi(av[1]);
	if (data.n_philo < 1)
		my_error_message("Incorrect inputs\n");
	init_struct(&data, ac, av);
	thread_creation(&data);

}
