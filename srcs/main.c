#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], fd);
}

void	my_error_message(char *message)
{
	ft_putstr_fd(message, 1);
	exit(-42);
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
/*
int	time_printing()
{

}
*/
void	printing(int code)
{
	if (code == 1)
		printf("%d %d has taken a fork", );
	if (code == 2)
		printf("%d %d is eating", );
	if (code == 3)
		printf("%d %d is sleeping", );
	if (code == 4)
		printf("%d %d is thinking", );
	if (code == 5)
		printf("%d %d died", );
}

void	*thread_function(t_data *data)
{
	(void)data;
	printf("im here\n");
	return (NULL);
}

void	thread_creation(t_data *data)
{
	int			i;	

	i = -1;
	while (++i < data->n_philo)
		pthread_create(&data->threads[i], NULL, thread_function(data), NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->threads[i], NULL);
	pthread_mutex_init(data->printing, NULL);

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
	while (++i < data->n_philo)
	{
		data->philos[i].time_to_die = ft_atoi(av[2]);
		data->philos[i].time_to_eat = ft_atoi(av[3]);
		data->philos[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data->philos[i].number_of_times_each_philosophers_must_eat = ft_atoi(av[5]);
		else
			data->philos[i].number_of_times_each_philosophers_must_eat = 0;
	}
}

int	main(int ac, char **av)
{	
	t_data	data;

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
//	printf("%d\n",data.philos[0].time_to_die);
//	printf("%d\n",data.philos[0].time_to_eat);
//	printf("%d\n",data.philos[0].time_to_sleep);
}



/*
typedef struct mutex_data
{
	int	data;
	pthread_mutex_t mutex;
}	mutex_data;

void	*thread_1(void *arg)
{
	int	*i;

	i = (int *)arg;
	(*i)++;
	pthread_exit(NULL);
}*/

/*
	int	i;
	pthread_t	thread1;
	
	i = 1;
	printf("avant, i = %d\n", i);
	pthread_create(&thread1, NULL, thread_1, &i);
	pthread_join(thread1, NULL);
	printf("apres, i = %d\n", i);
	return (EXIT_SUCCESS);
*/

