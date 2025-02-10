#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft.h"
#include "ft_printf.h"

int received = 0;

void signal_received()
{
    received = 1;
}

static void sendMessage(pid_t pid, int digit)
{
    int i = 7;
    while (i >= 0)
    {
        received = 0; 
        if ((digit >> i & 1) == 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        if (received == 0)
            usleep(500);
        i--;
    }
}

int main(int args0, char **args) 
{
    (void)args0;
    pid_t pid = atoi(args[1]);
    char *message = args[2];
    int len = ft_strlen(message);
    signal(SIGUSR1, signal_received);
    int i = 0;
    while (i < len)
    {
        sendMessage(pid, message[i]);
        i++;
    }
    sendMessage(pid, 0);
    return (0);
}