#include "philo.h"

#define IS_THINKING "%ld %d is thinking\n"
#define IS_EATING "%ld %d is eating\n"
#define IS_SLEEPING "%ld %d is sleeping\n"

void print_stat(char *str, t_philo *philo)
{
	bool is_died;

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

void	eating(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->forks_left);
		print_stat("%ld %d has taken a fork\n", philo);
		pthread_mutex_lock(philo->forks_right);
		print_stat("%ld %d has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->forks_right);
		print_stat("%ld %d has taken a fork\n", philo);
		pthread_mutex_lock(philo->forks_left);
		print_stat("%ld %d has taken a fork\n", philo);
	}

	print_stat(IS_EATING, philo);

	pthread_mutex_lock(&philo->wait);
	philo->last_time_to_eat = get_tm();
	pthread_mutex_unlock(&philo->wait);

	usleep(1000 * philo->data->time_to_eat);
	pthread_mutex_lock(&philo->wait);
	philo->counter++;
	philo->last_time_to_eat = get_tm();
	pthread_mutex_unlock(&philo->wait);
	pthread_mutex_unlock(philo->forks_left);
	pthread_mutex_unlock(philo->forks_right);
}

void	sleeping(t_philo *philo)
{
	print_stat(IS_SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}
void	is_odd_philo(t_philo *philo)
{
	if (philo->id % 2 && philo->data->number_of_philosophers % 2)
	{
		if (philo->data->time_to_eat > philo->data->time_to_sleep)
			usleep((philo->data->time_to_eat - philo->data->time_to_sleep) * 1000);
		usleep (1000);
	}
}
void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	bool is_died;

	
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->check_died);
		is_died = philo->data->is_died;
		if (is_died)
		{
			break;
		}
		pthread_mutex_unlock(&philo->data->check_died);
		eating(philo);
		sleeping(philo);
		print_stat(IS_THINKING, philo);
		is_odd_philo(philo);
	}
	pthread_mutex_unlock(&philo->data->check_died);
	return NULL;
}
