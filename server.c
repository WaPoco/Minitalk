/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:19:48 by vpogorel          #+#    #+#             */
/*   Updated: 2025/02/26 10:46:50 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

char	*g_text;

char	*re_alloc(char *str, int new_size)
{
	int		len;
	int		i;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc(new_size);
	if (!new_str)
	{
		if (g_text != NULL)
			free(g_text);
		ft_printf("Error allocating memory with malloc\n");
		exit(1);
	}
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	while (i < new_size)
		new_str[i++] = '\0';
	return (new_str);
}

void	resize(int c_letter, int *k, int *letter, int *text_len)
{
	if (c_letter >= *text_len)
	{
		if (*text_len == 0)
			(*text_len)++;
		g_text = re_alloc(g_text, 2 * (*text_len));
		(*text_len) *= 2;
	}
	g_text[c_letter - 1] = (char)(*letter);
	*letter = 0;
	*k = 0;
}

void	end_of_message(int *letter, int *k)
{
	static int	c_letter[1];
	static int	text_len[1];

	c_letter[0]++;
	if (*letter == 0)
	{
		if (c_letter[0] != 1)
			ft_printf("%s\n", g_text);
		free(g_text);
		g_text = NULL;
		c_letter[0] = 0;
		*k = 0;
		text_len[0] = 0;
		return ;
	}
	resize(*c_letter, k, letter, text_len);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	k;
	static int	letter;
	pid_t		client_pid;

	(void)context;
	client_pid = 0;
	if (info->si_pid != 0)
		client_pid = info->si_pid;
	if (signum == 12)
		letter = (1 << k) | letter;
	k++;
	if (k == 8)
		end_of_message(&letter, &k);
	if (client_pid != 0)
	{
		if (kill(client_pid, SIGUSR1) == -1)
		{
			printf("Error sending acknowledgment signal\n");
			if (g_text != NULL)
				free(g_text);
			exit(1);
		}
	}
}

int	main(void)
{
	struct sigaction	action;

	g_text = NULL;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	action.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
	{
		printf("Error receiving signal from server\n");
		if (g_text != NULL)
			free(g_text);
		exit(1);
	}
	printf("Server started. PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
