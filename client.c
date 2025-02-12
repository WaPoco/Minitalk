/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:30:29 by vpogorel          #+#    #+#             */
/*   Updated: 2025/02/12 19:34:15 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int	g_received;

void	signal_received(int t)
{
	(void)t;
	g_received = 1;
}

static void	send_message(pid_t pid, int digit)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_received = 0;
		if ((digit >> i & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		if (g_received == 0)
			pause();
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
