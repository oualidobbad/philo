/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:39 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/11 12:37:47 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_stat(char *str, t_philo *philo, int option)
{
	bool	end_simulation;

	if (option == 1)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf(str, get_tm() - philo->data->start_sumilation, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		return ;
	}
	pthread_mutex_lock(&philo->data->mutex_end_sumilation);
	end_simulation = philo->data->end_simulation;
	if (!end_simulation)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf(str, get_tm() - philo->data->start_sumilation, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	pthread_mutex_unlock(&philo->data->mutex_end_sumilation);
}

bool	allocate_forks_threads(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philosophers)
		return (false);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (free(data->philosophers), free(data), false);
	return (true);
}

void	ft_usleep(t_philo *philo, int time)
{
	if (philo->data->time_to_die < time)
		usleep(philo->data->time_to_die * 1000);
	else
		usleep(time * 1000);
}

long	get_tm(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
