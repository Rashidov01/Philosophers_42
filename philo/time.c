/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:44:27 by arashido          #+#    #+#             */
/*   Updated: 2023/09/21 13:15:35 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	initial_time;

	gettimeofday(&initial_time, NULL);
	return ((initial_time.tv_sec * 1000) + (initial_time.tv_usec / 1000));
}

long long	start_time(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000))
		- data->start);
}

void	ft_delay(t_philo *philo, int waiting_time)
{
	long long	first_time;
	long long	change;

	first_time = start_time(philo->philo_info);
	while (1)
	{
		pthread_mutex_lock(&philo->philo_info->time_lock);
		change = start_time(philo->philo_info) - first_time;
		if (change >= waiting_time)
		{
			pthread_mutex_unlock(&philo->philo_info->time_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_info->time_lock);
		usleep(100);
	}
}

void	philo_logs(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->philo_info->time_lock);
	if (!philo->philo_info->finish)
	{
		printf("%lld %d %s", start_time(philo->philo_info), philo->philo_id,
			message);
		pthread_mutex_unlock(&philo->philo_info->time_lock);
	}
	else
		pthread_mutex_unlock(&philo->philo_info->time_lock);
}