
#include "philo.h"

void	all_free(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosophers[i].forks_left);
		pthread_mutex_destroy(&data->philosophers[i].forks_right);
		i++;
	}
	free(data->philosophers);
	free(data->forks);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (ac < 5)
		return (1);
	if (parse_data(data, av) == 1)
	{
		printf("here\n");
		return 1;
	}
	data->start_sumilation = get_tm();
	creat_phiolosophers(data);
	all_free(data);
	return (0);
}
