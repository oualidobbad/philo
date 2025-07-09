#include "philo.h"

long	get_tm(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// printf("%ld\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_data_of_philo(t_data *data)
{
	int	i;

	i = 0;
	data->is_died = false;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philosophers[i].wait, NULL);
		data->philosophers[i].id = i + 1;
		data->philosophers[i].forks_left = data->forks[i];
		if (i == data->number_of_philosophers - 1)
			data->philosophers[i].forks_right = data->forks[0];
		else
			data->philosophers[i].forks_right = data->forks[i + 1];
		data->philosophers[i].last_time_to_eat = get_tm();
		data->philosophers[i].data = data;
		i++;
	}
}

void	creat_phiolosophers(t_data *data)
{
	int	i;
	pthread_t monitor;

	i = 0;
	pthread_create(&monitor, NULL, routine_check_died, data);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philosophers[i].philo, NULL, routine,
			&data->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].philo, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int parse_data(t_data *data, char **av)
{
	data->flag = 1;
	data->number_of_philosophers = ft_atoi(av[1], &data->flag);
	if (data->flag == 0)
		return (printf("Error\n check number of philosophers\n"), 1);
	data->time_to_die = ft_atoi(av[2], &data->flag);
	if (data->flag == 0)
		return (printf("Error\n check time to die\n"), 1);
	data->time_to_eat = ft_atoi(av[3], &data->flag);
	if (data->flag == 0)
		return (printf("Error\n check time to eat\n"), 1);
	data->time_to_sleep = ft_atoi(av[4], &data->flag);
	if (data->flag == 0)
		return (printf("Error\n check time to sleep\n"), 1);
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	init_data_of_philo(data);
	return 0;
}
