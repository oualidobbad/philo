#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>

typedef struct s_philo
{
	pthread_t philo;
	int		id;
	pthread_mutex_t forks_left;
	pthread_mutex_t forks_right;
	struct s_data *data; 
}t_philo;

typedef struct s_data
{
	int	number_of_philosophers;
	int time_to_die;
	int	time_to_eat;
	int	 time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int flag;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	t_philo *philosophers;
}t_data;

long	ft_atoi(char *nb, int *flag);
void *routine (void *arg);
void creat_piholosophers(t_data *data);
void parse_data(t_data *data, char **av);
void inizialize_data_of_philo(t_data *data);
#endif