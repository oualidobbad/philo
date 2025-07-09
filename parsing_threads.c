#include "philo.h"

long	get_tm(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	create_philosophers(t_data *data)
{
    int	i = 0;
    pthread_t monitor;

    data->someone_died = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_create(&data->philosophers[i].philo, NULL, routine,
            &data->philosophers[i]);
        i++;
    }
    pthread_create(&monitor, NULL, monitoring, data);

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_join(data->philosophers[i].philo, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
}

void	parse_data(t_data *data, char **av)
{
	data->flag = 1;
	data->number_of_philosophers = ft_atoi(av[1], &data->flag);
	if (data->flag == 0)
		exit((printf("Error\n check number of philosophers\n"), 1));
	data->time_to_die = ft_atoi(av[2], &data->flag);
	if (data->flag == 0)
		exit((printf("Error\n check time to die\n"), 1));
	data->time_to_eat = ft_atoi(av[3], &data->flag);
	if (data->flag == 0)
		exit((printf("Error\n check time to eat\n"), 1));
	data->time_to_sleep = ft_atoi(av[4], &data->flag);
	if (data->flag == 0)
		exit((printf("Error\n check time to sleep\n"), 1));
	if (av[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5], &data->flag);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	init_data_of_philo(data);
}
