/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:44 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/11 12:36:45 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->forks_left);
		print_stat("%ld %d has taken a fork\n", philo, 0);
		pthread_mutex_lock(philo->forks_right);
		print_stat("%ld %d has taken a fork\n", philo, 0);
	}
	else
	{
		pthread_mutex_lock(philo->forks_right);
		print_stat("%ld %d has taken a fork\n", philo, 0);
		pthread_mutex_lock(philo->forks_left);
		print_stat("%ld %d has taken a fork\n", philo, 0);
	}
	print_stat(IS_EATING, philo, 0);
	pthread_mutex_lock(&philo->mutex_of_time);
	philo->last_time_to_eat = get_tm();
	pthread_mutex_unlock(&philo->mutex_of_time);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->mutex_of_time);
	philo->counter++;
	pthread_mutex_unlock(&philo->mutex_of_time);
	pthread_mutex_unlock(philo->forks_left);
	pthread_mutex_unlock(philo->forks_right);
}

void	sleeping(t_philo *philo)
{
	print_stat(IS_SLEEPING, philo, 0);
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_stat(IS_THINKING, philo, 0);
	if (philo->id % 2 && philo->data->number_of_philosophers % 2)
	{
		if (philo->data->time_to_eat > philo->data->time_to_sleep)
			ft_usleep(philo, (philo->data->time_to_eat
					- philo->data->time_to_sleep));
		usleep(2000);
	}
}

void	start_routine(t_philo *philo)
{
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_end_sumilation);
		if (philo->data->end_simulation)
			break ;
		pthread_mutex_unlock(&philo->data->mutex_end_sumilation);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_mutex_unlock(&philo->data->mutex_end_sumilation);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->forks_left);
		print_stat("%ld %d has taken a fork\n", philo, 0);
		pthread_mutex_unlock(philo->forks_left);
	}
	else
		start_routine(philo);
	return (NULL);
}
