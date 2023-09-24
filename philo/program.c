/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <avazbekrashidov6@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:43:29 by arashido          #+#    #+#             */
/*   Updated: 2023/09/24 13:37:49 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_start(void *param)
{
	t_philo	*temp_philo;
	t_data	*temp_info;

	temp_philo = (t_philo *)param;
	temp_info = temp_philo->philo_info;
	if (temp_philo->philo_id % 2 == 0)
		usleep(1000);
	while (!temp_info->finish)
	{
		pthread_mutex_lock(&temp_philo->philo_info->program_lock);
		if (temp_info->meal_count > 0
			&& temp_philo->meals_count == temp_info->meal_count)
		{
			pthread_mutex_unlock(&temp_philo->philo_info->program_lock);
			break ;
		}
		pthread_mutex_unlock(&temp_philo->philo_info->program_lock);
		philo_eating(temp_philo);
		philo_sleeping(temp_philo);
		philo_thinking(temp_philo);
        usleep(100);
	}
	return (NULL);
}

static void	all_eat(t_data *data)
{
	int	total_meals;

	total_meals = 0;
	if (data->meal_count > 0)
	{
		while (total_meals < data->meal_count)
		{
			pthread_mutex_lock(&data->program_lock);
			if (data->philo[total_meals].meals_count < data->meal_count)
			{
				pthread_mutex_unlock(&data->program_lock);
				break ;
			}
			total_meals++;
			pthread_mutex_unlock(&data->program_lock);
		}
		if (total_meals == data->philo_count)
		{
			pthread_mutex_lock(&data->program_lock);
			data->finish = true;
			pthread_mutex_unlock(&data->program_lock);
		}
	}
}

void	philo_logs(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->philo_info->program_lock);
	if (!philo->philo_info->finish)
	{
		printf("%lld %d %s", start_time(philo->philo_info), philo->philo_id,
			message);
		pthread_mutex_unlock(&philo->philo_info->program_lock);
	}
	else
		pthread_mutex_unlock(&philo->philo_info->program_lock);
}

static void death_check(t_philo *philo)
{
    long long passed_time;

    if (philo->philo_info->finish == false)
    {
        pthread_mutex_lock(&philo->philo_info->program_lock);
        passed_time = start_time(philo->philo_info) - philo->last_meal;
        pthread_mutex_unlock(&philo->philo_info->program_lock);
        if (passed_time >= philo->philo_info->die)
        {
            philo_logs(philo, PHILO_DIED);
            pthread_mutex_lock(&philo->philo_info->program_lock);
            philo->philo_info->finish = true;
            pthread_mutex_unlock(&philo->philo_info->program_lock);
        }
    }
}

static void stat_program(t_data *data)
{
    int i;

    i = 0;
    while (!data->finish)
    {
        death_check(&data->philo[i]);
        all_eat(data);
        usleep(1000);
        if (i == data->philo_count - 1)
            i = -1;
        i++;
    }
}

int start_program(t_data *data)
{
    int i;

    i = -1;
    if (data->die < data->eat)
        data->eat = data->die;
    if (data->philo_count == 1)
    {
        for (i = 0; i < data->philo_count; i++)
            pthread_create(&data->philo[0].philo_thread, NULL, &philo_single, (void *)&data->philo[i]);
    }
    else
    {
        while (++i < data->philo_count)
            pthread_create(&data->philo[i].philo_thread, NULL, &philo_start,
                           (void *)&data->philo[i]);
        while (!data->finish)
            stat_program(data);
    }
    return (1);
}
