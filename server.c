#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft.h"
#include "ft_printf.h"

char *text = NULL;

char *re_alloc(char *str, int new_size)
{
  int len;
  char *new_str;
  int i;

  i = 0;
  len = ft_strlen(str);
  new_str = malloc(new_size);
  while (i < len)
  {
    new_str[i] = str[i];
    i++; 
  }
  free(str);
  while (i < new_size)
  {
    new_str[i] = '\0';
    i++; 
  }
  return (new_str);
}

void signal_handler(int signum, siginfo_t *info, void *context) 
{
  (void)context;
  static int k = 7;
  static int c_letter;
  static int letter;
  pid_t client_pid = 0;
  char *new_text;
  static int text_len;

  if (info->si_pid != 0)
    client_pid = info->si_pid;
  if (signum == 12)
    letter = (1 << k) | letter;
  k--;
  if (k < 0)
  {
    c_letter++;
    if (letter == 0)
    {
      kill(client_pid, SIGUSR1);
      if (c_letter != 1)
        ft_printf("%s\n", text);
      free(text);
      text = NULL;
      c_letter = 0;
      k = 7;
      text_len = 0;
      return ;
    }
    if (c_letter >= text_len)
    {
      if (text_len == 0)
        text_len++;
      new_text = re_alloc(text, 2 * text_len);
      text_len *= 2; 
      text = new_text;
    }
    text[c_letter - 1] = (char)letter; 
    letter = 0;
    k = 7;
  }
  if (client_pid != 0)
    kill(client_pid, SIGUSR1);
}

int main(void) 
{
  struct sigaction action;
  action.sa_flags = SA_SIGINFO;
  sigemptyset(&action.sa_mask);
  action.sa_sigaction = signal_handler;
  /*
  signal(SIGUSR1, signal_handler);
  signal(SIGUSR2, signal_handler);
  */
  sigaction(SIGUSR1, &action, NULL);
  sigaction(SIGUSR2, &action, NULL);
  printf("%d\n", getpid());
  printf("Process started. PID: %d\n", getpid());
  while (1) {
    //pause();
  }
  return (0);
}