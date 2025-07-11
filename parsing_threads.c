#include "philo.h"

void	init_data_of_philo(t_data *data)
{
	int	i;

	i = 0;
	data->is_died = false;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->check_died, NULL);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philosophers[i].wait, NULL);
		pthread_mutex_init(&data->philosophers[i].check, NULL);
		data->philosophers[i].id = i + 1;
		data->philosophers[i].forks_left = &data->forks[i];
		if (i == data->number_of_philosophers - 1)
            data->philosophers[i].forks_right = &data->forks[0];
        else
            data->philosophers[i].forks_right = &data->forks[i + 1];
        data->philosophers[i].last_time_to_eat = get_tm();
		data->philosophers[i].data = data;
		data->philosophers[i].counter = 0;
		i++;
	}
}

int parse_data(t_data *data, char **av)
{
	data->flag = 1;
	data->number_of_eats = -1;
	data->number_of_philosophers = ft_atoi(av[1], &data->flag);
	if (data->flag == 0)
		return (write (2, "Error\n check number of philosophers\n", 37), 1);
	data->time_to_die = ft_atoi(av[2], &data->flag);
	if (data->flag == 0)
		return (write (2, "Error\n check time to die\n", 26), 1);
	data->time_to_eat = ft_atoi(av[3], &data->flag);
	if (data->flag == 0)
		return (write (2, "Error\n check time to eat\n", 26), 1);
	data->time_to_sleep = ft_atoi(av[4], &data->flag);
	if (data->flag == 0)
		return (write(2, "Error\n check time to sleep\n", 28), 1);
	if (av[5])
	{
		data->number_of_eats = ft_atoi(av[5], &data->flag);
		if (data->flag == 0)
			return (write (2, "Error\n invalid nb eats\n", 24), 1);
	}
	if (!allocate_forks_threads(data))
		return (write (2, "fail malloc\n", 13), 1);
	init_data_of_philo(data);
	return 0;
}

void	creat_phiolosophers(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philosophers[i].philo, NULL, routine,
			&data->philosophers[i]);
			i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].philo, NULL);
		i++;
	}
}