#include "philo.h"

#define IS_THINKING "%ld %d \001\033[0;35m\002 is thinking \001\033[0m\002 🤔\n"
#define IS_EATING "%ld %d \033[38;5;208m is eating \001\033[0m\002 🍝\n"
#define IS_SLEEPING "%ld %d \001\033[1;32m\002 is sleeping\001\033[0m\002 💤\n"

void print_stat(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf(str, get_tm() - philo->data->start_sumilation, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}
void thinking(t_philo *philo)
{
	if (philo->data->is_died)
		return ;
	print_stat(IS_THINKING, philo);
}

void	sleeping(t_philo *philo)
{
	if (philo->data->is_died)
		return ;
	print_stat(IS_SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	if (philo->data->is_died)
		return ;
	pthread_mutex_lock(&philo->forks_left);

	print_stat("%ld %d  take left fork 🍴\n", philo);

	pthread_mutex_lock(&philo->forks_right);

	print_stat("%ld %d  take right fork 🍴\n", philo);
	print_stat(IS_EATING, philo);

	pthread_mutex_lock(&philo->wait);
	philo->last_time_to_eat = get_tm();
	pthread_mutex_unlock(&philo->wait);

	usleep(1000 * philo->data->time_to_eat);

	pthread_mutex_unlock(&philo->forks_left);
	pthread_mutex_unlock(&philo->forks_right);
	
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	if (philo->id % 2 == 1)
		usleep(3000);
	while (!philo->data->is_died)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return NULL;
}
