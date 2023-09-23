/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:55:28 by arashido          #+#    #+#             */
/*   Updated: 2023/09/23 22:11:09 by arashido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **argv)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
	{
		printf("%s\n", ARGV);
		printf("%s", ARGV);
		return (-1);
	}
	argv++;
	if (argv_checker(argv) == -1)
		return (-1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	init(argv, data);
	start_program(data);
	ft_free(data);
	return (0);
}
