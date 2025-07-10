#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	long			last_time_to_eat;
	int				counter;
	pthread_mutex_t wait;
	pthread_mutex_t check;
	pthread_mutex_t	*forks_left;
	pthread_mutex_t	*forks_right;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eats;
	int				number_of_times_each_philosopher_must_eat;
	int				flag;
	long			start_sumilation;
	bool			is_died;
	bool			is_sleeping;
	pthread_mutex_t check_died;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
}					t_data;

void    			*monitoring(void *arg);
long				ft_atoi(char *nb, int *flag);
long				get_tm(void);
void				*routine(void *arg);
void				all_free(t_data *data);
void				creat_phiolosophers(t_data *data);
int					parse_data(t_data *data, char **av);
void				init_data_of_philo(t_data *data);
void 				print_stat(char *str, t_philo *philo, int option);
#endif