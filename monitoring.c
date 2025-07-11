#include "philo.h"
bool    check_death(t_philo *philo)
{
    long time_last_meal;
    
    pthread_mutex_lock(&philo->wait);
    time_last_meal = get_tm() - philo->last_time_to_eat;
    pthread_mutex_unlock(&philo->wait);
    if (philo->data->time_to_die < time_last_meal)
    {
        pthread_mutex_lock(&philo->data->check_died);
        philo->data->is_died = true;
        pthread_mutex_unlock(&philo->data->check_died);
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
        pthread_mutex_lock(&data->philosophers[i].wait);
        if (data->number_of_eats != -1 && data->philosophers[i].counter >= data->number_of_eats)
            counter++;
        pthread_mutex_unlock(&data->philosophers[i].wait);
        if(check_death(&data->philosophers[i]) == true)
            return true;
        if (data->number_of_eats != -1 && counter >= data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->check_died);
            data->is_died = true;
            pthread_mutex_unlock(&data->check_died);
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