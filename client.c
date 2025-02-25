/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:30:29 by vpogorel          #+#    #+#             */
/*   Updated: 2025/02/25 18:22:11 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int	g_received;

void	error(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		printf("Error sending signal to client\n");
		exit(1);
	}
}

void	signal_received(int t)
{
	(void)t;
	g_received = 1;
}

static void	send_message(pid_t pid, int digit)
{
	int	i;
	int	signal;

	signal = 0;
	i = 0;
	while (i < 8)
	{
		if ((digit >> i & 1) == 0)
			signal = 10;
		else
			signal = 12;
		error(pid, signal);
		while (1)
		{
			if (g_received == 1)
			{
				g_received = 0;
				break ;
			}
			usleep(100);
		}
		i++;
	}
}

int	main(int args0, char **args)
{
	int		i;
	int		len;
	pid_t	pid;
	char	*message;

	if (args0 - 1 != 2 || !args[1] || !args[2])
	{
		ft_printf("Error arguments\n");
		return (0);
	}
	pid = ft_atoi(args[1]);
	message = args[2];
	len = ft_strlen(message);
	i = 0;
	g_received = 0;
	signal(SIGUSR1, signal_received);
	while (i < len)
		send_message(pid, message[i++]);
	send_message(pid, 0);
	return (0);
}
