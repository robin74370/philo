#include "philo.h"

unsigned long long	time_conversion()
{
	struct timeval tv;
	unsigned long long	time;
	
	(void)tv;
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	printing(int philo_id, int code, unsigned long long time)
{
//	if (code == 1)
//		printf("%d %d has taken a fork\n", philo_id );
//	if (code == 2)
//		printf("%d %d is eating\n", philo_id, );
	if (code == 3)
		printf("%d %llu is sleeping\n", philo_id, time);
//	if (code == 4)
//		printf("%d %d is thinking\n", philo_id, );
//	if (code == 5)
//		printf("%d %d died\n", philo_id, );
}

/*
void	check_died(t_data *data)
{
	if (data->died_count != 0)
		exit(-42);
}

void	is_thinking(int philos_id, t_data *data)
{

}

void	is_eating(int philos_id, t_data *data)
{
	//check si les fourchettes sont libres
	printing()
}
*/
void	is_sleeping(int philo_id, t_data *data)
{
	int		time;
	
	usleep(data->time_to_sleep / 10);
	time = time_conversion();
	printing(philo_id, 3, time);
}

void	*routine(void *data)
{
	int	i;
	t_data	*tmp;

	tmp = (t_data *)data;
	i = -1;
	while (++i < tmp->n_philo)
	{
//		if (tmp->philos[i].philo_id % 2 == 0)
//			is_eating(tmp->philos[i].philos_id, data);
//		else
			is_sleeping(tmp->philos[i].philo_id, data);
	}
	return (NULL);
}

void	thread_creation(t_data *data)
{
	int			i;	
	
	i = -1;
	while (++i < 5)
		pthread_create(&data->threads[i], NULL, routine, data);
	i = -1;
	while (++i < 5)
		pthread_join(data->threads[i], NULL);
//	pthread_mutex_init(data->printing, NULL);
//	pthread_mutex_init(data->eating, NULL);
}

void	init_struct(t_data *data, int ac, char **av)
{
	int	i;

	data->threads = malloc((data->n_philo) * sizeof(pthread_t));
	if (!data->threads)
		return ;
	data->philos = malloc((data->n_philo) * sizeof(t_philo));
	if (!data->philos)
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
//	struct	timeval start;
//	struct	timeval end;

//	gettimeofday(&start, NULL);
	if (!(ac >= 5 && ac <= 6))
		my_error_message("Wrong number of arguments\n");
	data.n_philo = atoi(av[1]);
	if (data.n_philo < 1)
		my_error_message("Incorrect inputs\n");
	data.philos = malloc((data.n_philo) * sizeof(t_philo));
	if (!data.philos)
		return (0);
	init_struct(&data, ac, av);
	thread_creation(&data);
//	gettimeofday(&start, NULL);
//	printf("%d\n", time_printing(&start, &end));
}
