#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED_BLINK "\e[1;5;31m"
# define OFF "\e[m"

# define IS_THINKING "%ld %d is thinking\n"
# define IS_EATING "%ld %d is eating\n"
# define IS_SLEEPING "%ld %d is sleeping\n"

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	long			last_time_to_eat;
	int				counter;
	pthread_mutex_t	mutex_of_time;
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
	int				flag;
	long			start_sumilation;
	bool			end_simulation;
	pthread_mutex_t	mutex_end_sumilation;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
}					t_data;

void				*monitoring(void *arg);
long				ft_atoi(char *nb, int *flag);
long				get_tm(void);
void				*routine(void *arg);
void				ft_usleep(t_philo *philo, int time);
void				all_free(t_data *data);
bool				creat_phiolosophers(t_data *data);
int					parse_data(t_data *data, char **av);
void				print_stat(char *str, t_philo *philo, int option);
bool				allocate_forks_threads(t_data *data);
void				all_free_and_destroy(t_data *data);
#endif