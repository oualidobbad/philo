#include "philo.h"
bool ft_is_died(t_data *data)
{
    int i;
    long time_last_meal;

    i = 0;
    time_last_meal = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_lock(&data->philosophers[i].wait);
        time_last_meal = get_tm() - data->philosophers[i].last_time_to_eat;
        pthread_mutex_unlock(&data->philosophers[i].wait);
        if (data->time_to_die < time_last_meal)
        {
            pthread_mutex_lock(&data->print);
            printf ("philo %d is died\n", data->philosophers[i].id); 
            pthread_mutex_unlock(&data->print);
            return true;
        }
        i++;
    }
    return false;
}
void    *routine_check_died(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    while (1)
    {
        if (ft_is_died(data) == true)
        {
            data->is_died = true;
            return NULL;
        }

    }
    return NULL;
}