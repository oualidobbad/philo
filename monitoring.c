#include "philo.h"
// RED \e[1;5;31m
// OFF \e[m
bool ft_is_died(t_data *data)
{
    int i;
    long time_last_meal;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_lock(&data->philosophers[i].wait);
        time_last_meal = get_tm() - data->philosophers[i].last_time_to_eat;
        pthread_mutex_unlock(&data->philosophers[i].wait);
        if (data->time_to_die < time_last_meal)
        {
            print_stat("%ld %d died\n", &data->philosophers[i]);
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
    while (1)
    {
        if (ft_is_died(data) == true)
        {
            return NULL;
        }
        usleep(1000);
    }
    return NULL;
}