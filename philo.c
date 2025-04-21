
#include "philo.h"

void	all_free(t_data *data)
{
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
	parse_data(data, av);
	creat_piholosophers(data);
	all_free(data);
	return (0);
}
