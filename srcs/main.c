#include "philo.h"

unsigned long long	time_conversion()
{
	struct timeval tv;
	unsigned long long	time;
	
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	printing(int philo_id, int code)
{
	unsigned long long time;

	time = time_conversion();
	if (code == 1)
		printf("%d %llu has taken a fork\n", philo_id, time);
	if (code == 2)
		printf("%d %llu is eating\n", philo_id, time);
	if (code == 3)
		printf("%d %llu is sleeping\n", philo_id, time);
	if (code == 4)
		printf("%d %llu is thinking\n", philo_id, time);
//	if (code == 5)
//		printf("%d %d died\n", philo_id, );
}

/*
void	check_died(t_data *data)
{
	if (data->died_count != 0)
		exit(-42);
}
*/
void	is_thinking(int philo_id, t_data *data)
{
	(void)data;
	printing(philo_id, 4);
}

void	is_eating(int philo_id, t_data *data)
{	
	pthread_mutex_lock(&data->fork[philo_id]);
	printing(philo_id, 1);
	if (philo_id == 1)
		pthread_mutex_lock(&data->fork[data->n_philo]);
	else
		pthread_mutex_lock(&data->fork[philo_id - 1]);
	printing(philo_id, 1);
	printing(philo_id, 2);
	usleep(data->time_to_eat * 1000);
}

void	is_sleeping(int philo_id, t_data *data)
{
	if (philo_id == 1)
		pthread_mutex_unlock(&data->fork[data->n_philo]);
	else
		pthread_mutex_unlock(&data->fork[philo_id - 1]);
	pthread_mutex_unlock(&data->fork[philo_id]);
	
	usleep(data->time_to_sleep * 1000);
	printing(philo_id, 3);
}

void	*routine(void *data)
{
	int	i;
	t_data	*tmp;

	tmp = (t_data *)data;
	i = 0;
	while (1)
	{
		if (i == tmp->n_philo)
			i = 0;
		is_eating(tmp->philos[i].philo_id, tmp);
		is_sleeping(tmp->philos[i].philo_id, tmp);
		is_thinking(tmp->philos[i].philo_id, tmp);
		i++;
	}
	return (NULL);
}

void	thread_creation(t_data *data)
{
	int			i;	
	
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->eating, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	data->time = time_conversion();
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
	data->philos = malloc((data->n_philo) * sizeof(t_philo));
	if (!data->philos)
		return ;
	data->fork = malloc((data->n_philo) * sizeof(pthread_mutex_t));
	if (!data->fork)
		return ;
	i = -1;
	while(++i < data->n_philo)
		data->philos[i].philo_id = i;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosophers_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosophers_must_eat = 0;
	i = 0;
	while(++i < data->n_philo + 1)
		data->philos[i - 1].philo_id = i;
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
