/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:42:31 by vpogorel          #+#    #+#             */
/*   Updated: 2025/02/26 10:44:51 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int	g_received;

void	error_args_pid(int args0, char **args, int pid)
{
	if (args0 - 1 != 2 || !args[1] || !args[2])
	{
		ft_printf("Error arguments\n");
		exit(1);
	}
	if (pid == 0)
	{
		ft_printf("Error reading pid\n");
		exit(1);
	}
}

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
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		error(pid, signal);
		while (!g_received)
			usleep(100);
		g_received = 0;
		i++;
	}
}

int	main(int args0, char **args)
{
	int						i;
	int						len;
	pid_t					pid;
	char					*message;
	struct sigaction		action;

	pid = ft_atoi(args[1]);
	error_args_pid(args0, args, pid);
	message = args[2];
	len = ft_strlen(message);
	i = 0;
	g_received = 0;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = signal_received;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
	{
		ft_printf("Error receiving aknowledgment signal\n");
		exit(1);
	}
	while (i < len)
		send_message(pid, message[i++]);
	send_message(pid, 0);
	return (0);
}
