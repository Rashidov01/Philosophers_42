/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:55:38 by arashido          #+#    #+#             */
/*   Updated: 2023/09/21 01:27:41 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ARGV "count_philo\ttime_2_die\ttime_2_eat\ttime_2_sleep\t[count_meal]\n"
# define ERR_ARGS "The argv must be positive int\n"
# define ERR_SIXTY_ARGS "Times should not be less than 60ms\n"
# define ERR_NUM_ARGS "This program takes 4 or 5 integer arguments:"
# define FORK_TAKEN "has taken a fork\n"
# define PHILO_EATING "is eating\n"
# define PHILO_DIED "died\n"
# define PHILO_THINKING "is thinking\n"
# define PHILO_SLEEPING "is sleeping\n"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					meal_count;
	int					philo_count;
	bool				finish;
	long long			die;
	long long			eat;
	long long			sleep;
	long long			start;
	pthread_mutex_t		init_lock;
	pthread_mutex_t		action_lock;
	pthread_mutex_t		time_lock;
	pthread_mutex_t		program_lock;
	pthread_mutex_t		philo_lock;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}						t_data;

typedef struct s_philo
{
	int					philo_id;
	int					left_fork;
	int					right_fork;
	int					meals_count;
	long long			last_meal;
	t_data				*philo_info;
	pthread_t			philo_thread;
	bool				holding_fork;
}						t_philo;

long long				current_time(void);
long long				start_time(t_data *data);
long long				ft_atoi(const char *str);
int						argv_checker(char **argv);
int						is_numeric(char *str);
int						start_program(t_data *data);
void					philo_eating(t_philo *philo);
void					philo_sleeping(t_philo *philo);
void					philo_thinking(t_philo *philo);
void					init(char **argv, t_data *data);
void					init(char **argv, t_data *data);
void					take_forks(t_philo *philo);
void					*ft_calloc(size_t count, size_t size);
void					ft_free(t_data *data);
void					ft_delay(t_philo *philo, int waiting_time);
void					*philo_single(void *param);
void					philo_logs(t_philo *philo, char *message);

#endif