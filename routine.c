#include "philo.h"

void	inizialize_data_of_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].forks_left = data->forks[i];
		if (i == data->number_of_philosophers - 1)
			data->philosophers[i].forks_right = data->forks[0];
		else
			data->philosophers[i].forks_right = data->forks[i + 1];
		data->philosophers[i].data = data;
		i++;
	}
}

void thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("P%d  is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("P%d  is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks_left);

	pthread_mutex_lock(&philo->data->print);
	printf("P%d  take left fork \n", philo->id);
	pthread_mutex_unlock(&philo->data->print);

	pthread_mutex_lock(&philo->forks_right);
	pthread_mutex_lock(&philo->data->print);
	printf("P%d  take right fork \n", philo->id);
	pthread_mutex_unlock(&philo->data->print);

	pthread_mutex_lock(&philo->data->print);
	printf ("P%d  is eating\n", philo->id);
	pthread_mutex_unlock(&philo->data->print);

	usleep(1000 * philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->forks_left);
	pthread_mutex_unlock(&philo->forks_right);
	
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	if (philo->id % 2 == 1)
		usleep(3000);
	while (1)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}