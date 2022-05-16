#include "philo.h"


void	printing(int code, t_data *data)
{
	static unsigned long long tmp = 0;
	unsigned long long time;


	if (!tmp)
		tmp = time_conversion();
	time = (time_conversion() - tmp);
	data->philos[data->philos->philo_id - 1].last_eat = time;
	if (code == 1)
		printf("%llu %d has taken a fork\n", time, data->philos->philo_id);
	if (code == 2)
		printf("%llu %d is eating\n", time, data->philos->philo_id);
	if (code == 3)
		printf("%llu %d is sleeping\n", time, data->philos->philo_id);
	if (code == 4)
		printf("%llu %d is thinking\n", time, data->philos->philo_id);
	if (code == 5)
		printf("%llu %d died\n", time, data->philos->philo_id);
}

/*
void	check_died(t_data *data)
{
	if (data->died_count != 0)
		exit(-42);
}
*/
void	is_thinking(t_data *data)
{
	(void)data;
	printing(4, data);
	//data->philos[philo_id - 1].status = 0;
}

void	is_eating(t_data *data)
{	
	int	time;
	static unsigned long long tmp = 0;
	
	(void)time;
	(void)tmp;
	if (!tmp)
		tmp = time_conversion();
	time = (time_conversion() - tmp);
	/*data->philos[data->philos->philo_id - 1].last_eat = time - data->philos[data->philos->philo_id - 1].last_eat;
	if (data->philos[data->philos->philo_id - 1].last_eat > data->time_to_die)
	{
		printing(5, data);
		exit(-42);
	}
	if (data->number_eat_each_philo != 0)
	{
		if (data->philos[data->philos->philo_id].eat_count == data->number_eat_each_philo)
			exit(-42);
	}*/
	pthread_mutex_lock(&data->fork[data->philos->philo_id]);
	printing(1, data);
	pthread_mutex_lock(&data->fork[data->philos->philo_id - 1]);
	printing(1, data);
	printing(2, data);
	usleep(data->time_to_eat * 1000);
	//data->philos[philo_id - 1].eat_count++;
//	data->philos[philo_id - 1].status = 1;
}

void	is_sleeping(t_data *data)
{

	pthread_mutex_unlock(&data->fork[data->philos->philo_id]);
	pthread_mutex_unlock(&data->fork[data->philos->philo_id - 1]);
	//pthread_mutex_unlock(&data->fork[philo_id]);
	usleep(data->time_to_sleep * 1000);
	printing(3, data);
}

void	*routine(void *data)
{
	int	i;
	t_data	*tmp;

	tmp = (t_data *)data;
	i = 0;
	while (1)
	{
		//if (tmp->philos[i].status == 0)
			is_eating(tmp);
		//if (tmp->philos[i].status == 1)
			is_sleeping(tmp);
		//if (tmp->philos[i].status == 2)
			is_thinking(tmp);
		i++;
	}
	return (NULL);
}

void	thread_creation(t_data *data)
{
	int			i;	
	
	data->time = time_conversion();
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->eating, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_create(&data->threads[i], NULL, &routine, data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->threads[i], NULL);
}

void	init_struct(t_data *data, int ac, char **av)
{
	int	i;

	data->philos = malloc((data->n_philo) * sizeof(t_philo));
	if (!data->philos)
		return ;
	data->threads = malloc((data->n_philo) * sizeof(pthread_t));
	if (!data->threads)
		return ;
	data->fork = malloc((data->n_philo) * sizeof(pthread_mutex_t));
	if (!data->fork)
		return ;
	i = 0;
	//while(++i < data->n_philo)
	//	data->philos[i].philo_id = i;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_eat_each_philo = ft_atoi(av[5]);
	else
		data->number_eat_each_philo = 0;
	i = -1;
	while(i++ < data->n_philo - 1)
		data->philos[i].philo_id = i + 1;

		
	
/*	i = -1;
	while (++i < data->n_philo)
		data->philos[i].eat_count = 0;
	i = -1;
	while (++i < data->n_philo)
		data->philos[i].status = 0;*/
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
