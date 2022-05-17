#include "philo.h"


void	printing(int code, t_philo *philo)
{
	static unsigned long long tmp;
	unsigned long long time;

	if (!tmp)
		tmp = time_conversion();
	time = (time_conversion() - tmp);
	philo->last_eat = time;
	printf("tiiiiime : %lld\n", time);
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
/*
void	check_died(t_data *data)
{
	if (data->died_count != 0)
		exit(-42);
}
*/
void	is_thinking(t_philo *philo)
{
	(void)philo;
	printing(4, philo);
	philo->status = 1;
}

void	is_eating(t_philo *philo)
{	
//	int	time;
	int							id_tmp;
	
	id_tmp = philo->philo_id;
//	time = (time_conversion() - tmp);
	pthread_mutex_lock(&philo->fork);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_lock(&philo->data_back->philos[0].fork);
	else
		pthread_mutex_lock(&philo->data_back->philos[id_tmp].fork);
	printing(1, philo);
	printing(1, philo);
	printing(2, philo);
	usleep(philo->data_back->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	if (philo->philo_id == philo->data_back->n_philo)
		pthread_mutex_unlock(&philo->data_back->philos[0].fork);
	else
		pthread_mutex_unlock(&philo->data_back->philos[id_tmp].fork);
	philo->status = 2;
}

void	is_sleeping(t_philo *philo)
{
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
		data->philos[i].philo_id = i + 1;
	i = -1;
	while (++i < data->n_philo)
		data->philos[i].data_back = data;
	i = -1;
	while (++i < data->n_philo)
		data->philos[i].status = 1;
	
	
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
