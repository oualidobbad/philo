#include "philo.h"

void print_stat(char *str, t_philo *philo, int option)
{
	bool is_died;

	if (option == 1)
	{
		pthread_mutex_lock(&philo->data->print);
		printf(str, get_tm() - philo->data->start_sumilation, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_lock(&philo->data->check_died);
	is_died = philo->data->is_died;
	if (!is_died)
	{
		pthread_mutex_lock(&philo->data->print);
		printf(str, get_tm() - philo->data->start_sumilation, philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->check_died);
}
bool allocate_forks_threads(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philosophers)
		return false;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return (free (data->philosophers), free (data), false);
	return true;
}
void ft_usleep (t_philo *philo, int time)
{
	if (philo->data->time_to_die < time)
		usleep(philo->data->time_to_die * 1000);
	else
		usleep(time * 1000);
}

long	get_tm(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
