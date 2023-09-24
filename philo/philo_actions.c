/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <avazbekrashidov6@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:10:52 by arashido          #+#    #+#             */
/*   Updated: 2023/09/24 12:07:29 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->program_lock);
	if (!philo->philo_info->finish)
	{
		pthread_mutex_unlock(&philo->philo_info->program_lock);
		take_forks(philo);
		philo_logs(philo, PHILO_EATING);
		pthread_mutex_lock(&philo->philo_info->program_lock);
		philo->last_meal = start_time(philo->philo_info);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->philo_info->program_lock);
		ft_delay(philo, philo->philo_info->eat);
		if (philo->holding_fork == true)
		{
			pthread_mutex_unlock(&philo->philo_info->fork[philo->left_fork]);
			pthread_mutex_unlock(&philo->philo_info->fork[philo->right_fork]);
			philo->holding_fork = false;
		}
	}
	else
		pthread_mutex_unlock(&philo->philo_info->program_lock);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->program_lock);
	if (!philo->philo_info->finish)
	{
		pthread_mutex_unlock(&philo->philo_info->program_lock);
		philo_logs(philo, PHILO_SLEEPING);
		ft_delay(philo, philo->philo_info->eat);
	}
	else
		pthread_mutex_unlock(&philo->philo_info->program_lock);
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->program_lock);
	if (!philo->philo_info->finish)
	{
		pthread_mutex_unlock(&philo->philo_info->program_lock);
		philo_logs(philo, PHILO_THINKING);
	}
	else
		pthread_mutex_unlock(&philo->philo_info->program_lock);
}
