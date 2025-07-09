#include "philo.h"

void	all_free(t_data *data)
{
    int i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philosophers[i].wait);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    free(data->philosophers);
    free(data->forks);
    free(data);
}

int	main(int ac, char **av)
{
    t_data	*data;

    if (ac < 5 || ac > 6)
        return (1);
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    parse_data(data, av);
    create_philosophers(data);
    all_free(data);
    return (0);
}