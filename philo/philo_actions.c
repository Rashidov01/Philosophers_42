/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:10:52 by arashido          #+#    #+#             */
/*   Updated: 2023/09/23 19:50:34 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_action(t_philo *philo)
{
	take_forks(philo);
	philo_logs(philo, PHILO_EATING);
	philo->last_meal = start_time(philo->philo_info);
	philo->meals_count++;
	ft_delay(philo, philo->philo_info->eat);
	if (philo->holding_fork == true)
	{
		pthread_mutex_unlock(&philo->philo_info->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->philo_info->fork[philo->right_fork]);
		philo->holding_fork = false;
	}
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->action_lock);
	if (!philo->philo_info->finish)
	{
		pthread_mutex_unlock(&philo->philo_info->action_lock);
		eat_action(philo);
	}
	else
		pthread_mutex_unlock(&philo->philo_info->action_lock);
}

void	philo_sleeping(t_philo *philo)
{
	if (!philo->philo_info->finish)
	{
		philo_logs(philo, PHILO_SLEEPING);
		ft_delay(philo, philo->philo_info->eat);
	}
}

void	philo_thinking(t_philo *philo)
{
	if (!philo->philo_info->finish)
		philo_logs(philo, PHILO_THINKING);
}
