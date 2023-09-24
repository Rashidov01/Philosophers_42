/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:10:52 by arashido          #+#    #+#             */
/*   Updated: 2023/09/24 15:42:45 by arashido         ###   ########.fr       */
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
		print_message(philo, PHILO_EATING);
		pthread_mutex_lock(&philo->philo_info->program_lock);
		philo->last_meal = start_time(philo->philo_info);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->philo_info->program_lock);
		ft_delay(philo, philo->philo_info->eat);
		if (philo->taken_fork == true)
		{
			pthread_mutex_unlock(&philo->philo_info->fork[philo->left_fork]);
			pthread_mutex_unlock(&philo->philo_info->fork[philo->right_fork]);
			philo->taken_fork = false;
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
		print_message(philo, PHILO_SLEEPING);
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
		print_message(philo, PHILO_THINKING);
	}
	else
		pthread_mutex_unlock(&philo->philo_info->program_lock);
}

void	print_message(t_philo *philo, char *message)
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
