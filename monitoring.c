#include "philo.h"
bool    check_death(t_philo *philo)
{
    long time_last_meal;
    
    pthread_mutex_lock(&philo->mutex_of_time);
    time_last_meal = get_tm() - philo->last_time_to_eat;
    pthread_mutex_unlock(&philo->mutex_of_time);
    if (philo->data->time_to_die < time_last_meal)
    {
        pthread_mutex_lock(&philo->data->mutex_end_sumilation);
        philo->data->end_simulation = true;
        pthread_mutex_unlock(&philo->data->mutex_end_sumilation);
        print_stat(RED_BLINK"%ld %d died\n"OFF, philo , 1);
        return true;
    }
    return false;
}

bool ft_is_died(t_data *data)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_lock(&data->philosophers[i].mutex_of_time);
        if (data->number_of_eats != -1 && data->philosophers[i].counter >= data->number_of_eats)
            counter++;
        pthread_mutex_unlock(&data->philosophers[i].mutex_of_time);
        if(check_death(&data->philosophers[i]) == true)
            return true;
        if (data->number_of_eats != -1 && counter >= data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->mutex_end_sumilation);
            data->end_simulation = true;
            pthread_mutex_unlock(&data->mutex_end_sumilation);
            return true;
        }
        i++;
    }
    return false;
}

void    *monitoring(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    while (!ft_is_died(data))
    {
    }
    return NULL;
}