/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:38:11 by arashido          #+#    #+#             */
/*   Updated: 2023/09/21 01:24:13 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*i;

	if (count != 0 && size != 0 && count > SIZE_MAX / size)
		return (NULL);
	i = malloc(count * size);
	if (i == NULL)
		return (NULL);
	bzero(i, count * size);
	return (i);
}

long long	ft_atoi(const char *str)
{
	int				index;
	unsigned int	result;
	int				sign;

	index = 0;
	result = 0;
	sign = 1;
	while (str[index] == 32 || (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = (result * 10) + str[index] - 48;
		index++;
	}
	return (result * sign);
}

int	argv_checker(char **argv)
{
	int	i;
	int	arg_value;

	i = -1;
	while (argv[++i])
	{
		arg_value = ft_atoi(argv[i]);
		if (is_numeric(argv[i]) == -1 || arg_value < 1
			|| ft_atoi(argv[0]) > 200)
		{
			printf("Error: Invalid ARGV\n");
			return (-1);
		}
		else if (i >= 1 && i <= 3)
		{
			if (arg_value < 60)
			{
				printf("Error: Argument %d must be at least 60.\n", i);
				return (-1);
			}
		}
	}
	return (0);
}

int	is_numeric(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		str++;
	}
	return (0);
}

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philo[i].philo_thread, NULL);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->philo_lock);
	free(data->philo);
	free(data->fork);
	free(data);
}
