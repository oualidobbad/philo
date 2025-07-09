#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
    pthread_t		philo;
    int				id;
    pthread_mutex_t	*forks_left;   // pointer to shared mutex
    pthread_mutex_t	*forks_right;  // pointer to shared mutex
    long			start_sumilation;
    long			last_time_to_eat;
    pthread_mutex_t	wait;
    struct s_data	*data;
}					t_philo;

typedef struct s_data
{
    int				number_of_philosophers;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				number_of_times_each_philosopher_must_eat;
    int				flag;
    pthread_mutex_t	*forks;
    pthread_mutex_t	print;
    t_philo			*philosophers;
    int             someone_died;
}					t_data;

long				ft_atoi(char *nb, int *flag);
void				*monitoring(void *arg);
long				get_tm(void);
void				*routine(void *arg);
void				create_philosophers(t_data *data);
void				parse_data(t_data *data, char **av);
void				init_data_of_philo(t_data *data);

#endif