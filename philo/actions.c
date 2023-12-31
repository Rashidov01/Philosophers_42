/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:35:37 by arashido          #+#    #+#             */
/*   Updated: 2023/09/24 14:38:46 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_odd_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->philo_info->fork[philo->right_fork]);
	print_message(philo, FORK_TAKEN);
	print_message(philo, FORK_TAKEN);
	philo->taken_fork = true;
}

static void	take_even_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->philo_info->fork[philo->left_fork]);
	print_message(philo, FORK_TAKEN);
	print_message(philo, FORK_TAKEN);
	philo->taken_fork = true;
}

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2)
		take_odd_forks(philo);
	else
		take_even_forks(philo);
}

void	*philo_single(void *param)
{
	t_philo	*temp_philo;

	temp_philo = (t_philo *)param;
	pthread_mutex_lock(&temp_philo->philo_info->fork[temp_philo->left_fork]);
	print_message(temp_philo, FORK_TAKEN);
	usleep((useconds_t)temp_philo->philo_info->die * 1000);
	pthread_mutex_unlock(&temp_philo->philo_info->fork[temp_philo->left_fork]);
	print_message(temp_philo, PHILO_DIED);
	pthread_mutex_lock(&temp_philo->philo_info->program_lock);
	temp_philo->philo_info->finish = true;
	pthread_mutex_unlock(&temp_philo->philo_info->program_lock);
	return (NULL);
}
