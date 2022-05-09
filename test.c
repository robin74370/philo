#include "./includes/philo.h"

void	*thread_function(int data)
{
	(void)data;
	return (NULL);
}

int	main()
{
	int			i;	
	pthread_t threads[5];
	i = 0;
	while (i < 5)
	{
		printf("%d\n", i);
		pthread_create(&threads[i], NULL, thread_function(i), NULL);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
