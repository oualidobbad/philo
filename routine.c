#include "philo.h"

void	init_data_of_philo(t_data *data)
{
    int	i = 0;
    pthread_mutex_init(&data->print, NULL);
    while (i < data->number_of_philosophers)
        pthread_mutex_init(&data->forks[i++], NULL);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].forks_left = &data->forks[i];
        if (i == data->number_of_philosophers - 1)
            data->philosophers[i].forks_right = &data->forks[0];
        else
            data->philosophers[i].forks_right = &data->forks[i + 1];
        data->philosophers[i].start_sumilation = get_tm();
        data->philosophers[i].last_time_to_eat = get_tm();
        data->philosophers[i].data = data;
        pthread_mutex_init(&data->philosophers[i].wait, NULL);
        i++;
    }
}

void	thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d  is thinking 🤔\n", get_tm() - philo->start_sumilation, philo->id);
    pthread_mutex_unlock(&philo->data->print);
}

void	sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d  is sleeping 💤\n", get_tm() - philo->start_sumilation, philo->id);
    pthread_mutex_unlock(&philo->data->print);
    usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
    pthread_mutex_lock(philo->forks_left);

    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d  take left fork 🍴\n", get_tm() - philo->start_sumilation, philo->id);
    pthread_mutex_unlock(&philo->data->print);

    pthread_mutex_lock(philo->forks_right);
    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d  take right fork 🍴\n", get_tm() - philo->start_sumilation, philo->id);
    pthread_mutex_unlock(&philo->data->print);

    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d  is eating  🍝\n", get_tm() - philo->start_sumilation, philo->id);
    pthread_mutex_unlock(&philo->data->print);

    usleep(1000 * philo->data->time_to_eat);

    pthread_mutex_lock(&philo->data->print);
    philo->last_time_to_eat = get_tm();
    pthread_mutex_unlock(&philo->data->print);

    pthread_mutex_unlock(philo->forks_left);
    pthread_mutex_unlock(philo->forks_right);
}

void	*routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 1)
        usleep(3000);
    while (!philo->data->someone_died)
    {
        thinking(philo);
        eating(philo);
        sleeping(philo);
    }
    return NULL;
}

void	*monitoring(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->philosophers[i].wait);
            long time_since_last_meal = get_tm() - data->philosophers[i].last_time_to_eat;
            if (time_since_last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->print);
                printf("%ld %d died 💀\n", get_tm() - data->philosophers[i].start_sumilation, data->philosophers[i].id);
                pthread_mutex_unlock(&data->print);
                data->someone_died = 1;
                pthread_mutex_unlock(&data->philosophers[i].wait);
                return NULL;
            }
            pthread_mutex_unlock(&data->philosophers[i].wait);
            i++;
        }
       usleep(1000); // Check every 1ms
    }
    return NULL;
}