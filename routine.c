#include "philo.h"

void	init_data_of_philo(t_data *data)
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
		data->philosophers[i].start_sumilation = get_tm();
		data->philosophers[i].last_time_to_eat = 0;
		data->philosophers[i].check_died = data->time_to_die;
		data->philosophers[i].data = data;
		i++;
	}
}

void thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d  is thinking 🤔\n", get_tm() - philo->start_sumilation, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d  is sleeping 💤\n",get_tm() - philo->start_sumilation, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks_left);

	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d  take left fork 🍴\n", get_tm() - philo->start_sumilation, philo->id);
	pthread_mutex_unlock(&philo->data->print);

	pthread_mutex_lock(&philo->forks_right);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d  take right fork 🍴\n", get_tm() - philo->start_sumilation, philo->id);
	pthread_mutex_unlock(&philo->data->print);

	pthread_mutex_lock(&philo->data->print);
	printf ("%ld %d  is eating  🍝\n", get_tm() - philo->start_sumilation, philo->id);
	pthread_mutex_unlock(&philo->data->print);

	usleep(1000 * philo->data->time_to_eat);

	pthread_mutex_lock(&philo->wait);
	philo->last_time_to_eat = get_tm() - philo->start_sumilation;
	pthread_mutex_unlock(&philo->wait);
	pthread_mutex_lock(&philo->wait);
	philo->check_died = philo->last_time_to_eat + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->wait);
	
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
		pthread_mutex_lock (&philo->wait);
		if (philo->check_died + 10 < (get_tm() - philo->start_sumilation) + philo->last_time_to_eat)
		{
			printf ("wa9et lmote %d\n xhal wsal %ld\n", philo->check_died, (get_tm() - philo->start_sumilation) + philo->last_time_to_eat);
			exit ((printf("philo %d died\n", philo->id), 0));
		}
		pthread_mutex_unlock(&philo->wait);
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}