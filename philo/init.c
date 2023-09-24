/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:38:59 by arashido          #+#    #+#             */
/*   Updated: 2023/09/24 14:38:46 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_data *data)
{
	int	i;

	data->fork = ft_calloc(data->philo_count, (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&data->program_lock, NULL);
	i = -1;
	data->philo = ft_calloc(data->philo_count, (sizeof(t_philo)));
	while (++i < data->philo_count)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->philo_count)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].meals_count = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_count;
		data->philo[i].philo_info = data;
		data->philo[i].last_meal = 0;
		data->philo[i].taken_fork = false;
	}
}

void	init(char **argv, t_data *data)
{
	data->philo_count = ft_atoi(argv[0]);
	data->die = ft_atoi(argv[1]);
	data->eat = ft_atoi(argv[2]);
	data->sleep = ft_atoi(argv[3]);
	if (argv[4])
		data->meal_count = ft_atoi(argv[4]);
	else
		data->meal_count = -1;
	data->finish = false;
	init_philo(data);
	data->start = current_time();
}
