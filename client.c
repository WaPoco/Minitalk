#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft.h"
#include "ft_printf.h"

int	received = 0;

void	signal_received()
{
	received = 1;
}

static void	sendMessage(pid_t pid, int digit)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		received = 0;
		if ((digit >> i & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		if (received == 0)
			pause();
		i--;
	}
}

int main(int args0, char **args) 
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
	message = ft_atoi(args[2]);
	len = ft_strlen(message);
	i = 0;
	signal(SIGUSR1, signal_received);
	while (i < len)
		sendMessage(pid, message[i++]);
	sendMessage(pid, 0);
	return (0);
}